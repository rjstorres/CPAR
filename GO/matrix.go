package main

import (
        "log"
        "fmt"
        "time"
    )

func min(x, y int) int {
        if x < y {
            return x
        }
        return y
}

func OnMult(n_a int, n_b int) {
        var temp int
        var i int
        var j int
        var k int
        c_lin := n_a
        c_col := n_b
        a := make([]int, n_a*n_a)
        b := make([]int, n_b*n_b)
        c := make([]int, c_lin*c_col)

        for i := 0; i < n_a*n_a; i++ {
		a[i] = 1
	}

        for i = 0; i < n_b*n_b; i++ {
                b[i] = (i + 1)
        }

        start := time.Now().UnixNano() / 1000000

        for i = 0; i < n_a; i++ {
                for j=0; j<n_b; j++ {
                        temp = 0
                        for k=0; k<n_a; k++ {
                            temp += a[i*n_a+k] * b[k*n_b+j]
                        }
                        c[i*n_a+j]=temp
                    }
        }

        end := time.Now().UnixNano() / 1000000
        fmt.Println("Result matrix:")

        for i = 0; i < min(c_lin*c_col, 10); i++ {
                fmt.Print(c[i])
                fmt.Print(" ")
        }
        fmt.Println()
        fmt.Println("\nTime MULT: %l")
        fmt.Println(end - start)
}
func OnMultLine(n_a int, n_b int) {
        var i int
        var j int
        var k int
        c_lin := n_a
        c_col := n_b
        a := make([]int, n_a*n_a)
        b := make([]int, n_b*n_b)
        c := make([]int, c_lin*c_col)
        for i = 0; i < n_a*n_a; i++ {
                a[i] = 1
        }
        for i = 0; i < n_b*n_b; i++ {
                b[i] = (i + 1)
        }

        start := time.Now().UnixNano() / 1000000
        for i = 0; i < n_a; i++ {
                for j=0; j<n_b; j++ {
                        for k=0; k<n_b; k++ {
                                c[i*n_a+j] += a[i*n_a+k] * b[k*n_b+j];
                        }
                    }
        }

        end := time.Now().UnixNano() / 1000000
        fmt.Println("Result matrix:")
        for i = 0; i <min(c_lin*c_col, 10); i++ {
                fmt.Print(c[i])
                fmt.Print(" ")
        }
        fmt.Println()

        fmt.Println("\nTime MULT:")
        fmt.Println(end - start)
}


func main() {
        op := 1
        for {
                fmt.Println("\n1. Multiplication")
                fmt.Println("\n2. Line Multiplication")
                fmt.Println("Selection?: ")
                
                if    _, err := fmt.Scan(&op);    err != nil {
                        log.Print("  Scan for i failed, due to ", err)
                        return
                }

                if op == 0 {
                        break
                }

                fmt.Println("Dimensions: lins cols ?")
                var lin int
                var col int
                if    _, err := fmt.Scan(&lin, &col);    err != nil {
                        log.Print("  Scan for i, j & k failed, due to ", err)
                        return
                }

                start := time.Now().UnixNano() / 1000000
                switch op {
                case 1:
                        OnMult(lin, col)
                case 2:
                        OnMultLine(lin, col)
                }
                end := time.Now().UnixNano() / 1000000
                fmt.Println("\nTime: %l")
                fmt.Println(end - start)
                if !(op != 0) {
                        break
                }
        }
}
