#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm> 

using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
};

struct CartItem {
    Product product;
    int quantity;
};

struct Transaction {
    vector<CartItem> items;
    double total;
}; 

void displayProducts(const vector<Product>& products) {
    cout << "Daftar Produk:\n";
    for (const auto& product : products) {
        cout << "ID: " << product.id << ", Nama: " << product.name 
             << ", Kategori: " << product.category 
             << ", Harga: Rp " << fixed << setprecision(2) << product.price << endl;
    }
} 

Product* findProductById(vector<Product>& products, int id) {
    for (auto& product : products) {
        if (product.id == id) {
            return &product;
        }
    }
    return nullptr;
} 

double calculateShippingCost(int distance) {
    return distance * 3000.0;
}

void displayCart(const vector<CartItem>& cart) {
    cout << "Keranjang Belanja:\n";
    for (const auto& item : cart) {
        cout << "Nama: " << item.product.name 
             << ", Jumlah: " << item.quantity 
             << ", Harga Total: Rp " << fixed << setprecision(2) << (item.product.price * item.quantity) << endl;
    }
} 

int main() {
    vector<Product> products = {
        {1, "Smartphone Samsung Galaxy S23", "Elektronik", 12000000},
        {2, "Laptop ASUS ROG Zephyrus G14", "Elektronik", 25000000},
        {3, "TV LED LG 43 Inch", "Elektronik", 6500000},
        {4, "Earbuds Apple AirPods Pro", "Elektronik", 3500000},
        {5, "Kamera DSLR Canon EOS 90D", "Elektronik", 17000000},
        {6, "Sepeda MTB Polygon", "Fitness", 5000000},
        {7, "Dumbbell 5kg", "Fitness", 200000},
        {8, "Matras Yoga", "Fitness", 250000},
        {9, "Mesin Elliptical", "Fitness", 7500000},
        {10, "Resistance Band", "Fitness", 100000},
        {11, "Serum Wajah Vitamin C", "Kecantikan", 150000},
        {12, "Masker Wajah Aloe Vera", "Kecantikan", 75000},
        {13, "Lipstik Matte L'Oréal", "Kecantikan", 120000},
        {14, "Parfum Chanel", "Kecantikan", 2500000},
        {15, "Sabun Cuci Muka Himalaya", "Kecantikan", 35000},
        {16, "Roti Tawar Serba Roti", "Konsumsi", 15000},
        {17, "Kopi Arabica 100g", "Konsumsi", 50000},
        {18, "Mie Instan", "Konsumsi", 5000},
        {19, "Susu UHT Indomilk 1 Liter", "Konsumsi", 18000},
        {20, "Teh Kotak Sosro 500ml", "Konsumsi", 7500},
    };

    vector<CartItem> cart;
    vector<Transaction> transactionHistory;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Produk\n";
        cout << "2. Tambah ke Keranjang\n";
        cout << "3. Lihat Keranjang\n";
        cout << "4. Hapus dari Keranjang\n";
        cout << "5. Checkout\n";
        cout << "6. Lihat Riwayat Pembayaran\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(products);
                break;
            case 2: {
                int productId, quantity;
                cout << "Masukkan ID produk: ";
                cin >> productId;
                Product* product = findProductById(products, productId);
                if (product) {
                    cout << "Masukkan jumlah: ";
                    cin >> quantity;
                    cart.push_back({*product, quantity});
                    cout << "Produk berhasil ditambahkan ke keranjang.\n";
                } else {
                    cout << "Produk tidak ditemukan.\n";
                }
                break;
            }
            case 3:
                displayCart(cart);
                break;
            case 4: {
                int productId;
                cout << "Masukkan ID produk yang ingin dihapus: ";
                cin >> productId;
                auto it = find_if(cart.begin(), cart.end(), [productId](const CartItem& item) {
                    return item.product.id == productId;
                });
                if (it != cart.end()) {
                    cart.erase(it);
                    cout << "Produk berhasil dihapus dari keranjang.\n";
                } else {
                    cout << "Produk tidak ditemukan di keranjang.\n";
                }
                break;
            }
            case 5: {
                int distance;
                cout << "Masukkan jarak pengiriman (km): ";
                cin >> distance;
                double shippingCost = calculateShippingCost(distance);
                double total = 0;
                for (const auto& item : cart) {
                    total += item.product.price * item.quantity;
                }
                total += shippingCost;
                transactionHistory.push_back({cart, total});
                cout << "Total pembayaran: Rp " << fixed << setprecision(2) << total << endl;
                cart.clear();
                break;
            }
            case 6: {
                cout << "Riwayat Pembayaran:\n";
                for (const auto& transaction : transactionHistory) {
                    cout << "Total: Rp " << fixed << setprecision(2) << transaction.total << endl;
                    for (const auto& item : transaction.items) {
                        cout << "Nama: " << item.product.name 
                             << ", Jumlah: " << item.quantity 
                             << endl;
                    }
                }
                break; 
            }
            case 0:
                cout << "Terima Kasih Sudah Mau Berbelanja Di BungkarnoShop.\n";
                break;
            default:
                cout << "Opsi tidak valid.\n";
        }
    } while (choice != 0);

    return 0;
}