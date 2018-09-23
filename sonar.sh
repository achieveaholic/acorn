#!/bin/sh

build-wrapper-linux-x86-64 --out-dir bw-output make clean all

sonar-scanner \
    -Dsonar.projectKey=$SONAR_PROJECT \
    -Dsonar.sources=. \
    -Dsonar.cfamily.build-wrapper-output=bw-output \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.organization=$SONAR_ORG \
    -Dsonar.login=$SONAR_USER
