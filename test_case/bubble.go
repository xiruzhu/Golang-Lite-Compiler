// Simple int array sort by bubble sort 
// assume we know the length of the array already
package main

func main() {
	var a []int;
	b := append(a,3,1,4,5,2,9,10);
	var n int = 6;
	for{		
		var flag = false;
		var i int;
		for i = 1; i <= n; i ++ {
			if b[ i-1 ] > b [i] {
				var tmp int = b[i];
				b[i] = b[i-1];
				b[i-1] = tmp;
				flag  = true;
			}
		}
		n = n - 1;
		if !flag {
			break
		}
	}
	print(b)
		
}
