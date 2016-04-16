// You can edit this code!
// Click here and start typing.
package main

func isPrime (number int) bool{
	for i := 2; i < number; i++{
	if(number%i == 0){
	  	return false;
		}
    }
  return true;
}

func nextPrime (number int) int{
	i := number + 1;
	for ;;{
      	    if isPrime(i) == true{
		return i;
	}
	i++
	}
}

func main() {
   next_prime := 4323231;
   for i:= 0; i < 5000; i++ {
   	next_prime = nextPrime(next_prime);
	println(next_prime)
   }
}
