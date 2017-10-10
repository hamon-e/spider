//
// ssl.cpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 01 17:14:07 2017 Benoit Hamon
// Last update Mon Oct 09 12:52:12 2017 Benoit Hamon
//
//

#include <iostream>
#include "Base64.hpp"
#include "CryptRSA.hpp"

int main(int argc, char *argv[]) {
    CryptRSA test;

    //test.genKey();

    std::string lol("BONJOUR123");
    std::string encrypt;
    std::string decrypt;

    //test.encrypt(lol, encrypt);

    //encrypt = Base64::encrypt(encrypt);
    //std::cout << encrypt << std::endl;

    //test.saveKeyInFile(ICryptAlgo::RSA_PRIV, "filename1");

    encrypt = "rWjScxYWsvBRuWf3c82Jae9tV6EGwHhmGiNr4vhT1wOKgecxhiN8oWvdOinAn9pmzlbbiHaV3JY+FCo+2nQ3SMqIGJpSHKeYNNtHkkasRU0wxcspPdf50bfUjvqX5zK6hXGr7bLaIeOGTzolOGn2NSjQYGzfC+LODWnPbsvozjUOoNe+7BoPKp2BVDGc6jyb1e9ybZiRIRoQwMDSWVO6bvS2ljIb39Ey0xybMbYp9QRLqBbmgH0kyA3JhgeUa8FLpX35KTbtXw9crtwXYuI+Pyf0py6zvWxlUxPKvsfe04lCsM+zTPlIlZoS0gVz0IAEshoS2wnuYhl+0IPrskxl2A==";

    encrypt = Base64::decrypt(encrypt);

    CryptRSA test2;
//    test.setKeyFromFile(ICryptAlgo::RSA_PUB, "filename");
    test2.setKeyFromFile(ICryptAlgo::RSA_PRIV, "./serverPrivKey.key");
//  std::string lol("BONJOUR123");
    // std::string encrypt;
//  std::string decrypt;

//encrypt = Base64::decrypt("WdkJsng1H4Bey/hYGm3leG9R4/rJWxtQfDkxqsVOrL/27A5IEgIdzjii/3J+UVBWaR+YNpg0VLwUM3JVFOkrNJbI0GJvfU9aAdta89rt4OBFLoYlzboLYnJ/tB2XzJwwB47zI1HSt4XqhsO1OVCh5xl5ggTL8FfBegYRAMV1A2CIj7mX8OsFDB6qLLShruSoEeRprbefeqiP5/ZPjp3a4+7i9zoxTHyCKZnVxYh6Ds4BEuw0WiUsk4eyqDDqif25eMWRkisjnYRpyThy/qB8Wv8KIh1drsTaxzxXfBgAccek1whygAiIN21GUJARxSzbCxJCwQNSLLDlTjWvWX7DTg==");
//    test.encrypt(lol, encrypt);
 //   std::cout << Base64::encrypt(encrypt) << std::endl;
    test2.decrypt(encrypt, decrypt);
    std::cout << "Decrypt:" << decrypt << std::endl;
//  std::string key;
  //  test.getKey(ICryptAlgo::RSA_PUB, key);
   //// std::cout << key << std::endl;
  //  test.getKey(ICryptAlgo::RSA_PRIV, key);
 //   std::cout << key << std::endl;
    return 0;
}
