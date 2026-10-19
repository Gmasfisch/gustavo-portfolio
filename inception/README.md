_This project has been created as part of the 42 curriculum by gfischba._

# Inception

## Description

Inception is a system administration project. The goal is to build a small web infrastructure entirely with Docker, inside a virtual machine, using only self-written Docker images.

The stack is composed of three services, each running in its own dedicated container:

- **MariaDB** — the database used by WordPress, listening on port 3306 (internal network only).
- **WordPress + php-fpm** — the website itself. PHP-FPM listens on port 9000 (internal network only) and executes the WordPress PHP code. WordPress is installed and configured automatically at container startup using wp-cli.
- **NGINX** — the single entrypoint of the infrastructure. It listens on port 443 only, terminates TLS (TLSv1.2/TLSv1.3 with a self-signed certificate), serves the static files of the website, and forwards PHP requests to the WordPress container over FastCGI.

The three containers communicate over a dedicated Docker bridge network. Two named volumes provide persistence (database data and website files), physically stored under `/home/gfischba/data` on the host. Everything is orchestrated with `docker compose` and driven by a `Makefile`.

## Instructions

### Prerequisites

- A Linux host (Virtual Machine)
- Docker Engine with the Docker Compose plugin
- `make` and `git`
- The domain configured locally: add `127.0.0.1 gfischba.42.fr` to `/etc/hosts`

### Configuration files (not included in the repository)

For security reasons, credentials are not versioned. Before building, create:

1. `srcs/.env` — non-sensitive environment variables (see `DEV_DOC.md` for the exact format).
2. `secrets/` — three files containing the passwords: `credentials.txt` (WordPress admin password on line 1, second user password on line 2), `db_password.txt` (database user password), `db_root_password.txt` (database root password).

### Build and run

```bash
make        # creates the data directories and builds + starts everything
make down   # stops and removes the containers (data is preserved)
make clean  # also removes the volumes and the data directories
make fclean # clean + full docker prune (images, build cache)
make re     # fclean + make
```

Once running, the website is available at `https://gfischba.42.fr` (the browser will warn about the self-signed certificate — this is expected) and the administration panel at `https://gfischba.42.fr/wp-admin`.

## Project description and design choices

The infrastructure is built from the penultimate stable Debian release (`bookworm`). Each image is built from its own Dockerfile and named after its service. Services are initialized at container startup by shell scripts (entrypoints) that configure the service on first run — using guards to stay idempotent across restarts — and then launch the service process in the foreground as PID 1, so the container's lifecycle matches the service's lifecycle (no infinite-loop hacks such as `tail -f` or `sleep infinity`).

Passwords are provided to the containers through Docker secrets, mounted as read-only files under `/run/secrets/`, and each service only receives the secrets it needs. Non-sensitive configuration goes through the mandatory `.env` file. Neither is committed to the repository.

### Virtual Machines vs Docker

Virtual Machine: Its an actual instalation of an OS, it will have its own kernel and resources, that will be taken from the host machine, and it will be much heavier because it needs much more files to run.

Docker: Docker is a software that containerizes services or applications. In this case, we are running an application with 3 containerized services. The containers have only the files that are required for that service to run, and it uses the host machine kernel and resources, so its much lighter and more portable.

Virtual Machine | Docker

Kernel: Own Kernel | Shares the host kernel.
Weight: GBs | MBs
Speed: Minutes | Seconds
Isolation: Completely Isolated | Shares kernel but isolates processes and filesystem.

### Secrets vs Environment Variables

Secrets: Files mounted by docker in /run/secrets inside of the container. They will contain the confidential information required for the services inside of the application. For example, root passwords, username passwords, administrator passwords, etc.

Environmental Variables: Its the variables that anyone with access to the containers can see, it includes all the information that is not confidential.

The reason for all of this is that, if the passwords are accessible to everyone, or are in a repository for example, anyone that has access to the repository, in github for example, would be able to see those passwords and change them. Also if you run docker inspect "project", and the passwords are inside of the enviromental variables, you would also be able to see them.

### Docker Network vs Host Network

Docker Network: Creates an isolated internal network where containers communicate with each other by name (e.g. wordpress, mariadb).
Only exposed ports are accessible from outside.

Host Network: The container shares the host machine's network directly,
with no network isolation between the container and the host.

In this project we use a bridge network called "inception" so that the containers can communicate internally, while only port 443 is exposed to the outside world.

### Docker Volumes vs Bind Mounts

Docker Volumes: Folders in the host machine that are managed by docker, stored internally at /var/lib/docker/volumes. Docker decides where they will live on the host. Data persists even if the container is stopped or removed.

Bind Mounts: Folders in the host machine that you create and manage, you specify the exact path, and Docker, through the bind option, connects them directly to the container. Any changes inside the container will aswell be reflected here.

## Resources

- Docker documentation (Docker Engine, Dockerfile reference, Compose file reference): https://docs.docker.com
- Docker Compose secrets: https://docs.docker.com/compose/how-tos/use-secrets/
- wp-cli documentation: https://wp-cli.org
- NGINX documentation (server blocks, FastCGI): https://nginx.org/en/docs/
- MariaDB documentation: https://mariadb.com/kb/en/
- OpenSSL `req` manual (self-signed certificates)
- Best practices for writing Dockerfiles and the PID 1 problem (Docker docs)

### AI usage

- This project was made using AI as a reviewer mainly and as a search engine for the correct understanding of the concepts.
- It was also used as a professor to review this same concepts, explain them to the AI and correct in case of mistakes or advices.
- Lastly, it was used to help set up the Virtual Machine and to review the User.doc, Dev.doc and Readme.md files for grammar and correctness.
