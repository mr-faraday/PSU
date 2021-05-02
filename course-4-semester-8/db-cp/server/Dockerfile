FROM alpine
RUN apk add --update nodejs nodejs-npm

WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
RUN npm prune --production

EXPOSE 3000

CMD [ "npm", "start" ]
