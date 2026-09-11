#include <string>
#include <vector>

struct Product{
   std::string name;
   std::string barcode;
   double price;
   int quantity = 0; 
};

std::vector<Product> CreateProduct(const std::string& filename);

void ShowProductInfo(const std::string& barcode);

void Case1();

void Case2(std::vector<Product>& products,int date,int& num);
   
void Checkout(std::string input2, std::vector<Product>& products, int date, int& num);

/*struct ProductRecord{
   std::string name;
   int record_quantity = 0; 
};
*/
