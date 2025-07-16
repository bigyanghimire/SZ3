rm -fr build/
rm -fr qsz/
mkdir qsz
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/bigyang/amg-compress/SZ3/qsz ..
make
make install
