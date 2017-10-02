//
// ssl.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 01 17:14:07 2017 Benoit Hamon
// Last update Mon Oct 02 22:29:31 2017 Benoit Hamon
//
//

#include <iostream>
#include "Base64.hpp"
#include "CryptRSA.hpp"
#include "CryptAES.hpp"

int main(int argc, char *argv[]) {
  CryptRSA test;

/*  test.genKey();

  std::string lol("BONJOUR123");
  std::string encrypt;
  std::string decrypt;
  test.encrypt(lol, encrypt);
  std::cout << Base64::encrypt(encrypt) << std::endl;
  test.decrypt(encrypt, decrypt);
  std::cout << decrypt << std::endl;
  std::string key;
  test.getKey(ICrypt::RSA_PUB, key);
  std::cout << key << std::endl;
  test.getKey(ICrypt::RSA_PRIV, key);
  std::cout << key << std::endl;
  test.saveKeyInFile(ICrypt::RSA_PUB, "filename");
  test.saveKeyInFile(ICrypt::RSA_PRIV, "filename1"); */


  test.setKeyFromFile(ICrypt::RSA_PUB, "filename");
  test.setKeyFromFile(ICrypt::RSA_PRIV, "filename1");
  std::string lol("BONJOUR123");
  std::string encrypt;
  std::string decrypt;

encrypt = Base64::decrypt("WdkJsng1H4Bey/hYGm3leG9R4/rJWxtQfDkxqsVOrL/27A5IEgIdzjii/3J+UVBWaR+YNpg0VLwUM3JVFOkrNJbI0GJvfU9aAdta89rt4OBFLoYlzboLYnJ/tB2XzJwwB47zI1HSt4XqhsO1OVCh5xl5ggTL8FfBegYRAMV1A2CIj7mX8OsFDB6qLLShruSoEeRprbefeqiP5/ZPjp3a4+7i9zoxTHyCKZnVxYh6Ds4BEuw0WiUsk4eyqDDqif25eMWRkisjnYRpyThy/qB8Wv8KIh1drsTaxzxXfBgAccek1whygAiIN21GUJARxSzbCxJCwQNSLLDlTjWvWX7DTg==");
//  test.encrypt(lol, encrypt);
  std::cout << Base64::encrypt(encrypt) << std::endl;
  test.decrypt(encrypt, decrypt);
  std::cout << decrypt << std::endl;
  std::string key;
  test.getKey(ICrypt::RSA_PUB, key);
  std::cout << key << std::endl;
  test.getKey(ICrypt::RSA_PRIV, key);
  std::cout << key << std::endl;
  return 0;
}
