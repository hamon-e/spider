#cd /tmp
#wget https://github.com/mongodb/mongo-c-driver/releases/download/1.8.0/mongo-c-driver-1.8.0.tar.gz
#tar xzf mongo-c-driver-1.8.0.tar.gz
#cd mongo-c-driver-1.8.0
#./configure --disable-automatic-init-and-cleanup
#make && make install

cd /tmp
wget https://github.com/mongodb/mongo-cxx-driver/archive/r3.0.3.tar.gz
tar -xzf r3.0.3.tar.gz
ls
cd mongo-cxx-driver-r3.0.3/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local \
  -DLIBBSON_DIR=/usr/lib/x86_64-linux-gnu/  \
  -DLIBMONGOC_DIR=/usr/lib/x86_64-linux-gnu/  \
  ..
#make EP_mnmlstc_core
make && make install
