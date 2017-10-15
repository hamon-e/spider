//
// ssl.cpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 01 17:14:07 2017 Benoit Hamon
// Last update Wed Oct 11 00:19:07 2017 Benoit Hamon
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

    std::string key = "LS0tLS1CRUdJTiBSU0EgUFJJVkFURSBLRVktLS0tLQpNSUlFcEFJQkFBS0NBUUVBMVdvS1F5c2FFbm5vVkxDaDgxT3luREJSQW9lSkhLN2xlWnJlWWJhMFUzZnYzUisvCldINkpQT2lsUVd6dllzaVNGZjRaQTk5eW9CN3RZcXE2dTlMUk5Ed2xnM2s4MnNzRzhzaWgvNlFJbzc3ZlZaSGUKVGNjT2owdlgvNFZCOEcxZ0lCekE2ait0cThPaFB0SmhmNmJJcklmd05Bb080dW1EczRzb2FMWGQzQ0Rad0wzcQpSbnN5UnZFRTcweWNndDhwRG56Tzdtb3FoK1RMOEt2QVdjVmZOZ2I3Y0JtaDljalJDRkN0aWpzTzZmMDU4bmEwCmVtRGZtSE1uQXNXWlEyZzJEclNPaFB0OHZ0TUdKTTVjYUF6QnJmUjBkSTQyaEMwVFB1NkowNk1FSnNUTmkxdlAKNEF3T1VQN0xlK2lkSHVRS0Qxc214aGkxT1VlSWRQNzlKei90S1FJREFRQUJBb0lCQUJKS2lXQ2laQlNyVUNkYQpFRGRidUJZODZlU09tMGpURUtYd2lSalU0UFc2ZE50OTZoZDZtT2FZaGZscWpjWG9yT1NucDVzMlhvdXN1dW5XCitqUTQ2R2RTdEdCbFZycmw1YzJQTnB0RGd0NE44UFJUa1RzWFVYOGtuL210Z1M1TElZNy9CK1hMMldXOFdhaVoKdlhPRVp2U3FuZ0xIemVqUzNNL1pvSGdCQm1ma1hMSkF6WFBYMzZlOTZ5eDdFMk1IYTU0VStFUDN3UDd5Yi83UApnNURvVnJoa0xLMFA4TGo5L1ZsdnZ3TnhNa25peVlaZG5pU09JZFQ1cGJSeUZWMVUyR1BXa1Z3dUlmTmxaYlNlCkUxKzlLVHo0eXhTcmFKaHV0K3piV3ppMkxuWEZJeDg4OVNSa2FrR2tmU3VVenJVcXRpMldDM3NoSFE2WTE3QUoKZS9QVWhNVUNnWUVBL1pQYlZ1RmpSdGZOdzZURW5tdXpMT0xCeWtUaVpwdG9ocDE2allrUkJtNzJIQWFLeDR5SQpqd2JNcE1tbWhlZFFiY1ZiU25uR3hWaFNST3NjUkxXRzduM0lLWllQZWNMZDFaNlkrQnZoN1ZrckhLeVgzQ0dHClZGZWhMWlN1c1hRSHhxbld6dEdRM1d5LytBdmJmc0dBbTNqQitJNy9oVmJTZUwxbjVRNjZuVnNDZ1lFQTEzUDEKOVgyTmgwYVlOT3YrMEtXRHBNZGtJbmpEWVZ0T2JJMzJRR3had2tDcTB6dVc0bVBYTUpPVkR4L1RDRFdJeGh1Tgp5VmJkV3Q5TnB6L3FKZDJWTGpIYW5GSE1tcGRiRjdyeks1d0ptd2xFQitrMTM3UERINHM1MmFyemN3T0ViUzZLCkM3U1VnR3RBdjZlUVVZdzRxb0hPT2xTYXdEeWNiUS9vbFpqNlVzc0NnWUVBNE1Wckszdmw4Q25pYm9WaTg3b3IKdktIVGZXUEorNEhPQ1dVVitOZUNpOTFYc2tmcVJDL0I3R1h1aURObXRGTHg3QnVBYkdlOVZiaVFWQjdEay9RRQpndXBqdnRrUkpyRWd5ZlluU2VZTlFjSkVnTXBNWWdnbGRpV203U3hhSFZub2VxU1prQUliRXVzT3p1UlR6K3ZkCi8vSHVubERERm9KN1ZpTXVNTS81Z3ZrQ2dZRUFtbDFYN1BKdXMyeE40eVR1cGJqZ2orL1grNmJBZllGNHQrZ2kKZGRmcm0zVFByNVl6TGJMUTI5bnhZeXV1L0dPMndoRzl6WEp5R0FpRHozL0ltQ2FoR3I3WFhVWnlMSlNpekdiQwprUTAwQ0tOajNiTW1TVWUzVm1OZktHZ0dFdktETCtLM1AxbTdTQ01QK2dEcE1yUWZhWEtsT2oraHZIZndyMmRGCmdlRmdBRzhDZ1lCMkloTVozL3hqa243cDRDSkVxMk9zL2l3ellQWHd1c1dSWUpFeWo0dS85b2ltVkgwbUovaHgKT3Z0ck9pcjBrNDIwdVZSejIrTEpzbTcrVHZMU1FYWDNqcFgzUlZuSkdvOW5lalc1dWdGVERPSEZMMFhSUTFuKwpneWVNeHovZUVKWnQzMUVZOS8xSS9FR1FSNDg4ZmFmZko1YnRidHlUNjVzTFduSUVWTUNtMWc9PQotLS0tLUVORCBSU0EgUFJJVkFURSBLRVktLS0tLQo=";
    encrypt = "DvYs6QKgcnjEZ73TlPOkjcWweCZ+RNj4RJK684DSk4JZcSDVaJvK1D7loRnr/wNDqAIWPzS6LuhLmnPiL5Qmarr892dEAXYMfq6TRnhqRaKkP8oDlK3rOxq3/MjrhfJA2Tkf7v8cd3/YccAHNfozbWvD5gqHFca569vZL2JSdiSsHtzSwDJeFylpLh9APNCLVREQDsVgHJkFk2DqqaCJ573kYjB8tjdqKuFhxoB/IZ2RAnRr9khD3Avl4RUn+Nw9Nw1CkJDv/QRDPQOjGCXJjcVukWGvUT+bGtWE037/zEHt2wxPDpGLWFsGSlFn/LBRf1/VL7xufG2HEqRcuprAYQ==";

    encrypt = Base64::decrypt(encrypt);
    key = Base64::decrypt(key);

    CryptRSA test2;
//    test.setKeyFromFile(ICryptAlgo::RSA_PUB, "filename");
    test2.setKey(ICryptAlgo::RSA_PRIV, key);
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
