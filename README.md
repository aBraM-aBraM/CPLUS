# C+

## Introduction

This repository contains a collection of c++ best practices I gather over time. It can be easily and contains a single header (macros.h)

The term **C+** refers to the usage of c++ in a way that produces the same code as C. This kind of behavior makes compiling to embedded devices much easier and increases performance.

## Standard Library
The c++ standard library is not consistent with allocations and exception usages. I have decided to use [ETL](https://github.com/ETLCPP/etl) as a standard library. In short ETL is a highly configurable cpp standard library targeted for embbeded devices.

## Examples (format)
Each example of a concept has its own .cpp file with comments
explaining the motives, advantages and disadvantages for the usages.