// You can edit this code!
// Click here and start typing.
package main

func isPrime (number int) bool{
	for i := 2; i < number; i++{
	if(number%float64(i) == 0){
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
   println(nextPrime(25325))
}

