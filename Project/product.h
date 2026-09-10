#include<string>
#include<vector>
struct Product{
   std::string name;
   std::string barcode;
   double price;
};

std::vector<Product> CreateProduct();