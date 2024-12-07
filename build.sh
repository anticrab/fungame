#!/bin/bash

docker build -t mingw-builder .
docker run --rm -v $(pwd):/app mingw-builder
