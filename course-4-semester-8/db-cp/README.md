# Database Course Project 4.2

Run server/client in development mode:

```sh
./startup.sh dev # server
npm run --prefix client start # client
```

Stopping:

```sh
docker-compose down
```

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
```
