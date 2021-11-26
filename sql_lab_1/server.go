package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strings"
)

func validUser(username string) bool {
	b := true
	lent := len(username)
	if lent > 7 {
		return false
	}
	for i := 0; i < lent; i++ {
		c := int(username[i])
		if i < 3 { // this is letters
			if !(c <= 122 && c >= 97) { // if not a lowercase letter
				b = false
			}
		} else if !(c <= 57 && c >= 48) { // if not a number
			b = false
		}
	}
	return b
}

func index(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "hello")
}

func login(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //get request method
	if r.Method == "GET" {
		t, _ := template.ParseFiles("templates/login.html")
		t.Execute(w, nil)
	} else {
		r.ParseForm()
		// logic part of log in
		fmt.Println("username:", r.Form["username"])
		fmt.Println("password:", r.Form["password"])
		username := r.FormValue("username")
		if username == "admin" || validUser(strings.ToLower(username)) {
			http.Redirect(w, r, "/manager", 307)
		} else {
			http.Redirect(w, r, r.Header.Get("Referer"), http.StatusSeeOther)
		}
	}
}

func ToLower(username string) {
	panic("unimplemented")
}

func manager(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	username := r.FormValue("username")
	t, _ := template.ParseFiles("templates/manager.html")
	type manager struct {
		Username string
		Content  string
	}
	var content string
	if username == "admin" {
		content = "welcome"
	} else {
		content = "You are not allowed here."
	}
	dynamic := manager{
		Username: username,
		Content:  content,
	}
	t.Execute(w, dynamic)
}

func main() {
	fs := http.FileServer(http.Dir("./static"))
	http.Handle("/static/", http.StripPrefix("/static/", fs))

	http.HandleFunc("/login", login)
	http.HandleFunc("/", index)
	http.HandleFunc("/manager", manager)
	err := http.ListenAndServe(":9090", nil) // setting listening port
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
