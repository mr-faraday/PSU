FROM alpine
RUN apk add --update nodejs npm

WORKDIR /app
COPY package*.json ./

ENV PYTHONUNBUFFERED=1
RUN apk add --update --no-cache python3 && ln -sf python3 /usr/bin/python
RUN python3 -m ensurepip
RUN pip3 install --no-cache --upgrade pip setuptools
RUN apk add --no-cache make gcc g++ && \
  npm ci && \
  npm rebuild bcrypt --build-from-source && \
  apk del make gcc g++

COPY . .
RUN npm prune --production

EXPOSE 3000

CMD [ "npm", "start" ]
