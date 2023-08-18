FROM ubuntu:18.04

#ENV HOME /root
SHELL ["/bin/bash", "-c"]

	RUN apt-get update && apt-get -y --no-install-recommends install \
	build-essential \
	g++ \
	cmake \
	#gbd \
	#wget \
	nano net-tools inetutils-ping

	WORKDIR /root/task2/
	COPY task_2/ .
	RUN mkdir build && cd build
	WORKDIR /root/task2/build
	RUN cmake ..
	RUN make
	CMD ["./main"]