# A single machine scheduling problem to minimize total early work

This repository suggest an implementation that I made for self-learning purposes.
It's not an official implementation of this paper.

It's not finished - it's a work in progress

# How to use
Main program:
```
g++ main.cpp; ./a.out
```

## create a dataset
Creates a dataset of 100 samples, and store it in the `data` folder.
Each sample has the same (n=10, pmax=50, alpha=0.7).
It calculate the desired output using full enumetarion.
```
g++ create_dataset.cpp; ./a.out
```

## test the dataset


## Credit

Yoav Ben-Yehoshua, Gur Mosheiov,
A single machine scheduling problem to minimize total early work,
Computers & Operations Research,
Volume 73,
2016,
Pages 115-118,
ISSN 0305-0548,
https://doi.org/10.1016/j.cor.2016.03.010.
(https://www.sciencedirect.com/science/article/pii/S0305054816300594)
