# selection-problem
分別使用 quick sort和 prune and search 來解決 selection problem，並比較這兩個方法的執行時間。
Input Size is  10000 to 30000 in steps 1000
每個數字為整數，範圍為[1,20000]
請勿使用函數庫中已經寫好的sort function
Input :
	給定檔名 “ Input.txt ”，其內容第一列有兩個數字n,k，以一空格隔開，n表示有n個數字，k表示取第k小的數字且1<=k<=n。
接著下一列有n個數字，每個數字之間以一空格隔開(請參考附檔) 
Outputs : 
	輸出兩個檔名 ” QS.txt ” 和 “ PS.txt ”，其內容需包含分別為使用 quick sort和 prune and search方法所找出的數字和程式執行時間. 第一列為找到第k小的數字，第二列為時間，時間輸出至小數第6位，單位為s(請參考附檔)
