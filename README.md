[![Build Status](https://travis-ci.org/alinous-core/codablecash.svg?branch=master)](https://travis-ci.org/alinous-core/codablecash)
[![Coverage Status](https://coveralls.io/repos/github/alinous-core/codablecash/badge.svg)](https://coveralls.io/github/alinous-core/codablecash)
# Codablecash

Scalable Smart Contract Ledger with rapid blockchain consensus.

## Consensus

Codablecash has two blockchains, which are Flash Consensus Chain and Main Data Chain.

The Flash Consensus Chain is used to fix order of transactions, and after that, transactions are validated, added into Main Data Chain.



### Instant Settlement

It makes rapid settlement possible, for 4 to 5 seconds.

### Sharding for Scalability


## Smart Contract

Codablecash has VM(Virtual Machine) to execute smart contract. The program written in original language is available.

The feature of the language is below.

 - Object Oriented Language
 - Build Relational Database Data Structure on blockchain data
 - Supports SQL 


### Offline and Online Execution



### Development Environment


# Testing

Codablecash is tested with following method.

 - Automated Testing
 - Coverage Check(result will be located on "target/html_report")
 - Memory Check by valgrind
 
The "sh" folder includes testing shell scripts.

