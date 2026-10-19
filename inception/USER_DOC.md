# User Documentation — Inception

This document explains how to use the Inception stack as an end user or administrator. No Docker knowledge is required beyond running the commands shown.

## What services does the stack provide?

The project runs a complete WordPress website served over HTTPS:

- **A public website** — a WordPress site reachable at `https://gfischba.42.fr`.
- **An administration panel** — the standard WordPress dashboard at `https://gfischba.42.fr/wp-admin`, used to write posts, manage users, and configure the site.
- **A database** — MariaDB, running in the background. It stores all the site content (posts, comments, users). You never interact with it directly; WordPress does.
- **A web server** — NGINX, also in the background. It is the only component exposed to the outside world, and it only accepts encrypted (HTTPS) connections on port 443.

## Starting and stopping the project

All commands are run from the root folder of the project.

| Action | Command | Effect on your data |
|---|---|---|
| Start (or rebuild and start) | `make` | Data is kept |
| Stop | `make down` | Data is kept — posts, users and settings survive |
| Full reset | `make clean` | **Deleted** — the site returns to a fresh install on next start |

The first `make` takes several minutes (it downloads and builds everything). Subsequent starts take a few seconds.

## Accessing the website and the administration panel

1. Open a browser and go to `https://gfischba.42.fr`.
2. The browser will display a security warning ("Your connection is not private" or similar). This is **expected**: the site uses a self-signed TLS certificate, meaning the connection is encrypted but no external authority has vouched for it. Click "Advanced" → "Proceed" to continue.
3. To administer the site, go to `https://gfischba.42.fr/wp-admin` and log in.

Two accounts exist:

- **Site administrator** — username `superuser`. Full control: themes, plugins, users, settings.
- **Editor** — username `editor`. Can write and manage content, but cannot change site settings.

## Locating and managing credentials

Passwords are never stored in the code repository. They live in two places on the host machine, at the root of the project:

- `secrets/credentials.txt` — WordPress passwords: line 1 is the administrator's, line 2 the editor's.
- `secrets/db_password.txt` — database user password.
- `secrets/db_root_password.txt` — database root password.
- `srcs/.env` — non-sensitive settings (domain name, usernames, site title, emails).

To change a password: edit the corresponding file, then run `make clean && make` (note: this resets site content), or change it directly from the WordPress admin panel (Users → edit user) to keep the content.

## Checking that the services are running correctly

Run:

```bash
docker ps
```

You should see **three** containers — `nginx`, `wordpress`, `mariadb` — all with a STATUS of `Up`. If one is missing or restarting, inspect its logs:

```bash
docker compose -f srcs/docker-compose.yml logs <service-name>
```

Quick functional checks:

```bash
# The site answers over HTTPS:
curl -k -sI https://gfischba.42.fr | head -1     # expected: HTTP ... 200

# Port 80 is closed (HTTPS only, by design):
curl -m 5 http://gfischba.42.fr                  # expected: connection error
```

If the site shows a database connection error right after startup, wait ~30 seconds: the services synchronize automatically on first boot.
