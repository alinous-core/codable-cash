FROM ubuntu:16.04


RUN apt-get update
RUN apt-get install -y libgmp-dev
RUN apt-get install -y cmake
RUN apt-get install -y g++
RUN apt-get install -y lcov

ADD ./make.sh /var/make.sh  

CMD ["/bin/bash"]