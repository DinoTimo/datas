# How to Compile

Building Datas
-----------
1. Clone the repository
   ```git clone git@github.com:DinoTimo/datas.git```
2. Create a build directory: `mkdir build && cd build`
3. Run cmake: `cmake .. `
4. Run make: `make datas`

Execute Datas
-----------
1. Run
    ```./datas [rmq|pr] in_file out_file```
2. Profit:
   On std::cerr some debug information is printed and some example requests and answers shown.
   On std::cout the result line, and only the result line is printed.


