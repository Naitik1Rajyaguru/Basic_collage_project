// This file is for functions only, lime add details, show details, transition of money and all..
// This is just for underastanding of public and private class and method and constructor.
package Bank_Functions;

import java.util.*;

abstract class demoinheritance{
	abstract void showAccount();
	abstract void depositmoney(long n);
	abstract void withdrawmoney(long n);
	abstract boolean search(String n);
}

public class Bank extends demoinheritance{
    public String accno;
    public String name;
    public long balance;
	public long deposite;
	public long withdrawal;
    public long Age;
    public int password;

    Scanner KB = new Scanner(System.in);

	// Constructor for enter details.
    public Bank(String accno, String name, long balance,long Age,int password ) {

        this.accno = accno;
        this.name = name;
        this.balance = balance;
        this.Age = Age;
        this.password = password;
    }

    //method to display account details
    public void showAccount() {
        
        System.out.format("%7s %14s %11s %7s"+"   ****",accno,name,balance,Age,password);
        System.out.println(); 
        System.out.println("---------------------------------------------------------------------------------------------\n\n");
         
    }

    //method to deposit money
    public void depositmoney(long amt) { 
		
        balance = balance + amt;
    }

    //method to withdraw money
    public void withdrawmoney(long amt) {                  
        if (balance-100 >= amt) {
            balance = balance - amt;
        } else {
            System.out.println("Less Balance then you need to have..Transaction Failed..!!");
        }
    }

    //method to search an account number
   public  boolean search(String acn) {
        if(accno.equals(acn)) {
            //showAccount();
            return (true);
        }
        return (false);
    }
}
