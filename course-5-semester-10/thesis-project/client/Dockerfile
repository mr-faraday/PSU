FROM alpine as build
RUN apk add --update nodejs npm

WORKDIR /app
COPY package*.json /app
RUN npm ci
COPY . /app
RUN npm run build
# RUN npm prune --production

FROM nginx:latest
COPY --from=build /app/build /var/www/html
COPY ./nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
