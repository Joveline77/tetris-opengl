rm -rf build 
mkdir build
cd build && cmake ..

cp -r ../src/shaders .
cp -r ../src/resources .

make -j4 && ./Tetris && cd ..
