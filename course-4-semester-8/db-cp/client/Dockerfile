FROM alpine
RUN apk add --update nodejs nodejs-npm

WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
RUN npm run build
RUN npm prune --production

EXPOSE 5000

CMD [ "npm", "run", "server:start" ]
