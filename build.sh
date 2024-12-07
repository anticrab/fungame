#!/bin/bash

docker build -t mingw-builder .
docker run --rm mingw-builder
