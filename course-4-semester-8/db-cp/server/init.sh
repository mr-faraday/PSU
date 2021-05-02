if [ ! -d "node_modules" ]
then
    mkddir ../app-pckg
    cp package*.json ../app-pckg
    cd ../app-pckg
    npm install
    mv package*.json ../app
    mv node_modules ../app
    cd ..
    rm app-pckg
    cd app
fi

npm run dev
