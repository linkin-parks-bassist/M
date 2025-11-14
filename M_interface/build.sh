#!/bin/bash

cd ../ && python codegen.py && cd - && idf.py build
