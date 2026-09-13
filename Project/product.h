#include <string>
#include <vector>

struct Product{
   std::string name;
   std::string barcode;
   double price;
   int quantity = 0; //指购物车中的物品数量，不记录进product.csv，每次购物结束后会被清空
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

bool Judge(std::string& line1, std::string& line2, std::string& line3, const std::string& barcode, bool& valid);
