#!/bin/bash

message=""
tag=""

while getopts m:t: flag
do
    case "${flag}" in
        m) message=${OPTARG};;
        t) tag=${OPTARG};;
    esac
done

git add *.c *.h *.sh *.txt makefile
if [ "$message" = "" ]
then
    git commit
else
    git commit -m "$message"
fi
git push origin
git status

if [ "$tag" != "" ]
then
    git tag $tag
    git push origin $tag
fi
