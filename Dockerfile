From debian:latest

RUN apt-get update
RUN apt-get -y install cmake g++ git wget
RUN apt-get -y install pkg-config
RUN apt-get -y install libboost-all-dev
RUN apt-get -y install libssl-dev
RUN apt-get -y install libbson-dev
RUN apt-get -y install libmongoc-dev

RUN cp /usr/include/libbson-1.0/* /usr/include/
RUN cp /usr/include/libmongoc-1.0/* /usr/include/

COPY ./mongo.sh /tmp/mongo.sh
RUN chmod +x /tmp/mongo.sh && /tmp/mongo.sh

ENV LD_LIBRARY_PATH /usr/local/lib:/usr/lib/x86_64-linux-gnu

RUN mkdir -p /root/spider
WORKDIR /root/spider

ADD . .

RUN cmake .
RUN make spider_serveur
