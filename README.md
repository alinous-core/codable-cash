[![Build Status](https://travis-ci.org/alinous-core/codablecash.svg?branch=master)](https://travis-ci.org/alinous-core/codablecash)
[![Coverage Status](https://coveralls.io/repos/github/alinous-core/codablecash/badge.svg)](https://coveralls.io/github/alinous-core/codablecash)
# Codablecash

Scalable Smart Contract Ledger with rapid blockchain consensus. The Codablecash is for Dapp application platform which has RDBMS on the blockchain data.

**Current development status **   

Now making first alpha version.
 - [Official Website](https://www.codablecash.org/ "Codablecash")
 - [Latest Jenkins Status](http://ci.codablecash.org/job/codablecash_develop/ "develop branch")
 - Author's Twitter [@TomohiroIizuka](https://twitter.com/TomohiroIizuka "Tomohiro Iizuka") 
 - [How to build and test](sh/README.md)


## Consensus

Codablecash has two blockchains, which are "Flash Consensus Chain" and "Main Data Chain".

The "Flash Consensus Chain" is used to fix order of transactions, and after that, transactions are validated, added into "Main Data Chain".


### Instant Settlement

It makes rapid settlement possible, for 4 to 5 seconds. After a transaction is broadcasted, following process is executed.


1.  Settlement
2.  Register into Ledger

When the transaction is imported into the "Flash Consensus Chain", it is sure that the transaction will be validated.
Therefore by checking it, users can check the transaction is settled on very early timing.

After the transaction is registered into "Main Data Chain", received coin becomes spendable.


### Sharding for Scalability

In order to execute transactions processing parallelly, multiple chains can work simultaneously.
The "Main Data Chain" absorbs difference of transaction numbers of each shard, and makes maintenance(Soft fork for update) easy.

### Finalizing Blockchain

Codablecash can finalize blockchain rapidly. Therefore it can use snapshot to make blockchain data compact.


## Smart Contract

Codablecash has VM(Virtual Machine) to execute smart contract. The program written in original language is available.

The feature of the language is below.

 - Object Oriented Language
 - Build Relational Database Data Structure on blockchain data
 - Supports SQL 


### Off-Chain and On-Chain Execution

The Smart Contract program contains Off-Chain and On-Chain parts.
Off-Chain part makes it possible to cooperate with external devices(Web Service, IoT, etc).

### Development Environment

Codablecash has Eclipse Plugin based IDE to develop Smart Contract program. It contains following feature.

 - Code Editor
     - Syntax Hilight
     - Content Assist
     - Break Points Support
 - Simulator & Debugger

# Testing

Codablecash is tested with following method.

 - Automated Testing
 - Coverage Check(result will be located on "target/html_report")
 - Memory Check by valgrind
 
The "sh" folder includes testing shell scripts.

