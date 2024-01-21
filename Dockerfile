FROM sdukshis/cppml

# Install dependencies
RUN apt-get update && apt-get install -y \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /usr/local/include

RUN mkdir -p /usr/local/include/eigen3
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz && \
    tar -xzvf eigen-3.4.0.tar.gz --strip-components=1 -C /usr/local/include/eigen3 && \
    rm eigen-3.4.0.tar.gz

RUN ln -s /usr/local/include/eigen3/Eigen/ /usr/local/include/Eigen

RUN apt-get upgrade

WORKDIR /usr/src/app
