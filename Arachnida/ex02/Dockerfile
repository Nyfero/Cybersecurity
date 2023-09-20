FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    libncurses5-dev \
    libncursesw5-dev \
    libreadline6-dev \
    libsqlite3-dev \
    libssl-dev \
    libxml2-dev \
    libxslt1-dev \
    libyaml-dev \
    zlib1g-dev \
    libjpeg-dev \
    libpng-dev \
    libgif-dev \
    && rm -rf /var/lib/apt/lists/*

# # Use an existing base image
# FROM alpine:latest

# # Install libpng-dev
# RUN apk update && apk add --no-cache libpng-dev

WORKDIR /app

COPY . /app

CMD ["bash"]
