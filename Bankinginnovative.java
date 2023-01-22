// This is main file.. every main details will be here.. like what kind of operation you want to do.. and all...

// Basic input-output, conditional statments, arry object, class, constructor, method, littel bit of inheritance and override, filing.

import java.util.*;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import Bank_Functions.*;


class Bankinginnovative {
    public static void main(String arg[]) {
		int AdminPassword = 8486;
        Scanner sc = new Scanner(System.in);
		/*try{
			FileWriter fwrite = new FileWriter("info.txt"); 
		}
		catch(IOException e){
			System.out.println("this is error!!");
		}*/
        System.out.println("\n------Bank Management System------- \n");
        Bank[] C;           // Array
        C = new Bank[5000];          // Kind of array of objects
        int ch,total=0;
		int i;
		

		// do-while loop --- just for something different :) 
        do {
            System.out.println("---------------------------------------------------------------------------------------------");
            System.out.println("                           >>>>>>>>Main Menu<<<<<<<<");
            System.out.println("---------------------------------------------------------------------------------------------");
            System.out.println(" 1. Add Customer");
            System.out.println(" 2. Display All");
            System.out.println(" 3. Search By Account");
            System.out.println(" 4. Deposit");
            System.out.println(" 5. Withdrawal");
            System.out.println(" 6. Exit\n");
            System.out.print("->Enter your Choice : ");
            ch = sc.nextInt();
            switch (ch) {
                 
                case 1:
				
				int d=1,k=0,fla=1;;
                System.out.print("Enter Name: ");
                String name=sc.next();
                System.out.print("Enter Account No: ");
                String accno= sc.next();
				
				while(true){
					fla=1;
					for(int g=0; g<total; g++){
						if(accno.equals(C[g].accno)){
							System.out.println("Sorry you have to chose different account number: ");
							fla=0;
							break;
						}
					}
					if(fla == 0){
						accno= sc.next();
					}
					else{
						break;
					}
				}
				System.out.print("Enter password of your account No: ");
                int password= sc.nextInt();
                System.out.print("Enter Age: ");
                long Age=sc.nextLong();
				while(Age>120){
					System.out.println("Youe ages is more then excepted sorry we don't have facility for you to open account");
					Age=sc.nextLong();
					k++;
					if(k==2){
						d=0;
						break;
					}
				}
				
				// Age less then 18 , restriction warning..
				if(Age<18){
					System.out.println("Remember your age is not 18 or more so in first time when you open account you can not add more then some restriction amount..");
				}
				
                System.out.print("Enter Balance: ");
                long bal=sc.nextLong();
				
				// Not sufficient balance warning..
				while(bal<100){
					System.out.println("You need to at least deposite 100rs!!");
					System.out.println("Want to enter money again ??  if yes then say yes");
					String yn=sc.next();
					if(yn.equals("Yes") || yn.equals("yes")){
						bal=sc.nextLong();
					}
					else{
						d=0;
						break;
					}
				}
				
				// Age less then 18 and amount of total money warning..
				if(Age<18){
					while(bal>100000){
					System.out.println("You cant deposite amout grater then 1 lakh!!");
					System.out.println("Want to enter money again ?? if yes then say yes");
					String yn;
					yn=sc.next();
						if(yn.equals("yes") || yn.equals("Yes")){
							bal=sc.nextLong();
						}
						else{
							d=0;
							break;
						}
					}
				}
				// If they are not entering money means account will not be generate.
				if(d==0){
					break;
				}
					
                C[total] = new Bank(accno, name, bal, Age,password);
                total++;
				System.out.println("Account succesfully created.. welcome to the bank");
                /////////////////////////////////////////////////
				try {  
                     
                    // writing the content into the FileOperationExample.txt file 
					// FileWriter is class in this we are giving it file name and if we want to cancanate things we will write true.
					// See the fileing methods you will be more clear.
                    FileWriter fwrite = new FileWriter("info.txt", true); 
                    fwrite.write("Name: "+C[total-1].name);
                    fwrite.write("   Account No: "+C[total-1].accno);
                    //fwrite.write("   Balance: "+C[total-1].balance);
                    fwrite.write("   password: "+C[total-1].password);
					fwrite.write("\n");
                    fwrite.close(); 
                
                    // Closing the stream       
                    //System.out.println("Content is successfully wrote to the file.");  
                } 
				catch (IOException e) {  
                    System.out.println("Unexpected error occurred");  
                    e.printStackTrace();  
                }  
                    ///////////////////////////////////////////////

                break;

					
                case 2:
					int x;
					System.out.println("Please enter admin password for acess details of every one.");
					x = sc.nextInt();
					if(x == AdminPassword){
						System.out.println(	"---------------------------------------------------------------------------------------------");
						System.out.printf("%5s %10s %12s %7s  %5s", "Account No", "NAME", "Balance","Age","password");   	// Formated out-put : like in c we do %.4f and all.....
						System.out.println();
						System.out.println(		"---------------------------------------------------------------------------------------------");
						for (i = 0; i < total; i++) {
							C[i].showAccount();
						}
					}
					else{
						System.out.println("Incorrect password....you can't acess this details...");
					}
					
					
                break;

                case 3:
				
                    System.out.print("->Enter Account No. You Want to Search....: ");
                    String acn = sc.next();
					System.out.println("->Enter password: ");
					int pass = sc.nextInt();
					
                    boolean found = false;
					if(total == 0){
						System.out.println("Sorry but first you need to creat account!");
						break;
					}
                    for (i = 0; i < total; i++) {
                        found = C[i].search(acn);
                        if (found) {
							System.out.println("---------------------------------------------------------------------------------------------");
							if(pass == C[i].password){
								C[i].showAccount();
							}
							else{
								System.out.println("Sorry but your password in wrong!!  you cant see details of this account");
							}
                            break;
                        }
                    }
                    if (!found) {
                        System.out.println("Search Failed..Account Not Exist..");
                    }
					
                break;

                case 4:
					
					if(total == 0){
						System.out.println("Sorry but first you need to creat account!");
						break;
					}
                    System.out.print("->Enter Account No : ");
                    acn = sc.next();
					//System.out.println("->Enter password: ");
					//int pass = sc.nextInt();
                    found = false;
					
                    for (i = 0; i < total; i++) {
                        found = C[i].search(acn);
                        if (found) {
							//if(pass == C[i].password){
								System.out.println("Enter deposite amount: ");
								C[i].deposite = sc.nextLong();
								while(( C[i].deposite + C[i].balance > 100000 ) && C[i].Age<18){
									System.out.println("Your Age is leass then 18 you cant have more then 1 lakh rupees enter amount less then: "+ (100000-C[i].balance));
									C[i].deposite = sc.nextLong();
								}
								C[i].depositmoney(C[i].deposite);
								break;
							//}
							/*else{
								System.out.println("You have entered wrong password!!  You cant see details of this account");
								break;
							}*/
						}
                    }
                    if (!found) {
                        System.out.println("Search Failed..please confirm accont number..");
						break;
                    }
					
					/////////////////////////////////////////////////
					try {                  
						// writing the content into the FileOperationExample.txt file 
						// FileWriter is class in this we are giving it file name and if we want to cancanate things we will write true.
						// See the fileing methods you will be more clear.
						FileWriter fedit = new FileWriter("trasiction.txt", true); 
						fedit.write("************************");
						fedit.write("\nthis Account have some movment please contat bank if you didn't did it.\n");
						fedit.write("Account details are:\n");
						fedit.write("Name: "+C[i].name);
						fedit.write("   Account No: "+C[i].accno+"\n");
						fedit.write("It had done deposite of money: "+ C[i].deposite+"\n");
						fedit.write("Now total amount is: "+C[i].balance+"\n");
						//fedit.write("   Balance: "+C[total-1].balance);
						fedit.write("************************\n");
						fedit.write("\n\n\n");
						fedit.close();                 	
					} 
					catch (IOException e) {  
						System.out.println("Unexpected error occurred");  
						e.printStackTrace();  
					}  
                    ///////////////////////////////////////////////
					
                break;

                case 5:
					
					if(total == 0){
						System.out.println("Sorry but first you need to creat account!");
						break;
					}
                    System.out.print("->Enter Account No : ");
                    acn = sc.next();
					System.out.println("->Enter password: ");
					pass = sc.nextInt();
                    found = false;
					
                    for (i = 0; i < total; i++) {
                        found = C[i].search(acn);
                        if (found) {
							if(pass == C[i].password){
								System.out.println("Enter Withdraw amount: ");
								C[i].withdrawal = sc.nextLong();
								C[i].withdrawmoney(C[i].withdrawal);
							}
							else{
								System.out.println("you have entered wrong password!! sorry you cant withdraw money.");
							}
							                            
                            break;
                        }
                    }
                    if (!found) {
                        System.out.println("Search Failed..Account Not Exist..");
						break;
                    }
					
					/////////////////////////////////////////////////
					try {                  
						// writing the content into the FileOperationExample.txt file 
						// FileWriter is class in this we are giving it file name and if we want to cancanate things we will write true.
						// See the fileing methods you will be more clear.
						FileWriter fedit = new FileWriter("trasiction.txt", true); 
						fedit.write("************************");
						fedit.write("this Account have some movment please contat bank if you didn't did it.\n");
						fedit.write("Account details are:\n");
						fedit.write("Name: "+C[i].name);
						fedit.write("   Account No: "+C[i].accno+"\n");
						fedit.write("It had done transiction of money: "+ C[i].withdrawal+"\n");
						fedit.write("Now total amount is: "+C[i].balance+"\n");
						//fedit.write("   Balance: "+C[total-1].balance);
						fedit.write("************************");
						fedit.write("\n\n\n");
						fedit.close();                 	
					} 
					catch (IOException e) {  
						System.out.println("Unexpected error occurred");  
						e.printStackTrace();  
					}  
                    ///////////////////////////////////////////////
					
                break;

                case 6:
                    
					
						// File fedit = new File("trasiction.txt"); 
						// if(fedit.delete()){
						// 	System.out.println("");
						// }

						System.out.println("Thans for use this simulation tell your friends to use this and learn things!! ....byy....");
						
                break;
				
				default:
					System.out.println("Please enter proper choise..");
					
				break;
            }
        } 
        while (ch != 6);
    }
}
