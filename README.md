# Simple Shop Management System
This is a simple shop management system that allows you to add, delete, modify, display, and purchase products. The products are stored in a binary file called **product.dat** and the transactions are stored in a binary file called **transaction.dat**.

# Features
- Add Product
- Delete Product
- Modify Product
- Display Products
- Purchase Product

# Add Product
The user can add a new product by selecting the Add Product option. The program prompts the user to enter the product details such as ID, name, price, quantity, and cost. The product details are then written to the product.dat file.

# Delete Product
The user can delete a product by selecting the Delete Product option. The program prompts the user to enter the ID of the product to be deleted. If the product is found in the product.dat file, it is deleted from the file. Otherwise, the program displays a message indicating that the product was not found.

# Modify Product
The user can modify a product by selecting the Modify Product option. The program prompts the user to enter the ID of the product to be modified. If the product is found in the product.dat file, the program prompts the user to enter the new product details such as name, price, quantity, and cost. The product details are then updated in the product.dat file.

# Display Products
The user can display all the products in the inventory by selecting the Display Products option. The product details such as ID, name, price, quantity, and cost are read from the product.dat file and displayed on the screen.

# Purchase Product
The user can purchase a product by selecting the Purchase Product option. The program prompts the user to enter the ID of the product to be purchased. If the product is found in the product.dat file, the program prompts the user to enter the quantity to be purchased. If the quantity is available in the inventory, the program calculates the total cost of the products and writes the transaction details such as ID, name, price, quantity, cost, and profit to the transaction.dat file. The program also updates the quantity of the product in the product.dat file.

# Usage
To run the program, simply compile the inventory.c file and run the resulting executable. The program will display a menu of options that the user can select from. Follow the on-screen prompts to perform the desired action.

# Credits
C-Simple-ShopManager was created by sirawat
