# Developer Documentation — Inception

This document describes how to set up, build, and manage the project from a developer's perspective.

## 1. Setting up the environment from scratch

### Prerequisites

- A Debian-based Linux system (the project is designed to run inside a Debian virtual machine).
- **Docker Engine** and the **Docker Compose plugin** — install following the official guide "Install Docker Engine on Debian" (`docker-ce`, `docker-ce-cli`, `containerd.io`, `docker-compose-plugin`). Add your user to the `docker` group (`sudo usermod -aG docker $USER`, then log out and back in).
- **make** and **git**: `sudo apt install make git`.
- Local domain resolution: `echo "127.0.0.1 gfischba.42.fr" | sudo tee -a /etc/hosts`.

### Configuration files to create (not versioned)

Credentials are excluded from the repository by `.gitignore`. After cloning, create:

**`srcs/.env`** — non-sensitive environment variables:

```
DOMAIN_NAME=gfischba.42.fr

MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser

WP_TITLE=My Inception Site
WP_ADMIN_USER=superuser
WP_ADMIN_EMAIL=super@example.com
WP_USER=editor
WP_USER_EMAIL=editor@example.com
```

Note: the WordPress admin username must not contain "admin"/"administrator" (subject requirement).

**`secrets/`** — three password files at the repository root:

```bash
mkdir -p secrets
# line 1: WP admin password, line 2: WP second user password
printf "%s\n%s\n" "ADMIN_PASSWORD" "EDITOR_PASSWORD" > secrets/credentials.txt
echo "DB_USER_PASSWORD"  > secrets/db_password.txt
echo "DB_ROOT_PASSWORD"  > secrets/db_root_password.txt
```

These are mounted into the containers by Docker Compose as read-only files under `/run/secrets/`, and read by the init scripts at startup.

## 2. Building and launching

Everything goes through the `Makefile` at the repository root, which drives `docker compose` with `srcs/docker-compose.yml`:

| Target | What it does |
|---|---|
| `make` | Creates `~/data/mysql` and `~/data/wordpress`, then `docker compose up --build -d` |
| `make down` | Stops and removes containers and network; volumes/data preserved |
| `make clean` | `down -v` + removes `~/data` (destroys all data) |
| `make fclean` | `clean` + `docker system prune -af` (removes all images and build cache) |
| `make re` | `fclean` + `make` |

The three images are built from the Dockerfiles in `srcs/requirements/<service>/` and are named after their service (`mariadb`, `wordpress`, `nginx`). Only NGINX publishes a port to the host (`443:443`).

On first start, the entrypoint scripts initialize each service (database and users creation, WordPress installation via wp-cli). Both scripts use guards (`if` checks on the persistent data) so restarts skip initialization. The WordPress script actively waits for MariaDB to accept connections before installing — `depends_on` alone only orders container startup.

## 3. Managing containers and volumes

```bash
# Status of the containers
docker ps                      # running
docker ps -a                   # including stopped/crashed

# Logs of a service (most useful debugging tool)
docker compose -f srcs/docker-compose.yml logs mariadb
docker compose -f srcs/docker-compose.yml logs -f wordpress   # follow live

# Open a shell inside a container
docker exec -it wordpress bash

# Query the database directly
docker exec -it mariadb mariadb -u root -p wordpress -e "SHOW TABLES;"
# (password: content of secrets/db_root_password.txt)

# Inspect images, volumes, network
docker images
docker volume ls
docker volume inspect srcs_db_data
docker network inspect srcs_inception
```

## 4. Data storage and persistence

Two **named volumes** are declared in `docker-compose.yml`, using `driver_opts` so that their data lives at a fixed host location, as required by the subject:

| Volume | Mounted at (container) | Host location | Contains |
|---|---|---|---|
| `db_data` | `/var/lib/mysql` (mariadb) | `~/data/mysql` | The MariaDB databases |
| `wp_data` | `/var/www/wordpress` (wordpress **and** nginx) | `~/data/wordpress` | The WordPress files |

`wp_data` is shared by two containers: WordPress writes the site files, NGINX reads them to serve static content.

Persistence behavior:

- `make down` / container crash / VM reboot → **data survives**. On restart, the init scripts detect existing data (guards) and skip re-installation.
- On the very first start, Docker copies the WordPress files already present in the image into the empty volume, which is how they end up in `~/data/wordpress`.
- `make clean` / `make fclean` → volumes and `~/data` are deleted; the next `make` performs a fresh installation.
