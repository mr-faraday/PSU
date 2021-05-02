if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    exit 1
fi

if [ $1 != "prod" ] && [ "$1" != "dev" ]
  then
    echo "Arguments must be 'prod' or 'dev'"
    exit 1
fi

if [ $1 == "dev" ] && [ $2 == "build" ]
    then
        docker-compose -f docker-compose.yml -f docker-compose.dev.yml build
    else
        if [ $1 == "dev" ]
          then
            docker-compose -f docker-compose.yml -f docker-compose.dev.yml up -d
        fi
fi

if [ $1 == "prod" ] && [ $2 == "build" ]
    then
            docker-compose -f docker-compose.yml -f docker-compose.prod.yml build
    else
        if [ $1 == "prod" ]
          then
            docker-compose -f docker-compose.yml -f docker-compose.prod.yml up -d
        fi
fi




