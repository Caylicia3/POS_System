#include<string>
#include<vector>
struct Product{
   std::string name;
   std::string barcode;
   double price;
};

std::vector<Product> CreateProduct(const std::string& filename);

void ShowProductInfo(const std::string& barcode);

void Case1();