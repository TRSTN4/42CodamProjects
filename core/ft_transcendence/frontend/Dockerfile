FROM node:18 AS build

WORKDIR /app

COPY package.json package-lock.json ./

RUN npm install

COPY . .

EXPOSE 3000

RUN npm run build

RUN npm install -g serve

CMD ["serve", "-s", "dist", "-l", "3000"]