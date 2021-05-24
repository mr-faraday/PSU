# Database Course Project 4.2

Backup database:

```sh
docker exec -t database pg_dumpall -c -U postgres > dump_`date +%d-%m-%Y"_"%H_%M_%S`.sql
# or compressed
docker exec -t database pg_dumpall -c -U postgres | gzip > dump_`date +%d-%m-%Y"_"%H_%M_%S`.gz
```

Restore database:

```sh
cat %DUMB_FILE% | docker exec -i database psql -U postgres
```

Reuired .env config:

```sh
POSTGRES_PASSWORD= ... # database password
POSTGRES_USER= ... # database password
POSTGRES_DB= ... # database name

JWT_SECRET= # secret for generate JWT tokens
```
