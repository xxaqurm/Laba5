package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Client struct {
	id   string
	time int
}

type Window struct {
	totalTime int
	clients   []string
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	// Ввод количества окон
	var windowCount int
	for windowCount < 1 {
		fmt.Print("Введите количество окон: ")
		scanner.Scan()
		input := scanner.Text()
		count, err := strconv.Atoi(strings.TrimSpace(input))
		if err != nil || count < 1 {
			fmt.Println("Количество окон должно быть больше 0.")
			continue
		}
		windowCount = count
	}

	windows := make([]Window, windowCount)
	var clients []Client
	clientID := 1

	// Основной цикл команд
	for {
		fmt.Print("Введите команду (ENQUEUE <время>, DISTRIBUTE): ")
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}

		cmd := strings.ToUpper(parts[0])

		switch cmd {
		case "ENQUEUE":
			if len(parts) != 2 {
				fmt.Println("Формат: ENQUEUE <время>")
				continue
			}
			time, err := strconv.Atoi(parts[1])
			if err != nil || time < 1 {
				fmt.Println("Время должно быть положительным числом.")
				continue
			}
			clients = append(clients, Client{
				id:   "T" + strconv.Itoa(clientID),
				time: time,
			})
			clientID++

		case "DISTRIBUTE":
			if len(clients) == 0 {
				fmt.Println("Нет клиентов в очереди.")
				continue
			}

			// Сортировка по убыванию времени
			sort.Slice(clients, func(i, j int) bool {
				return clients[i].time > clients[j].time
			})

			for _, client := range clients {
				bestIndex := 0
				minTime := windows[0].totalTime
				for i := 1; i < windowCount; i++ {
					if windows[i].totalTime < minTime {
						minTime = windows[i].totalTime
						bestIndex = i
					}
				}
				windows[bestIndex].totalTime += client.time
				windows[bestIndex].clients = append(windows[bestIndex].clients, client.id)
			}

			clients = nil // очищаем очередь
			goto PRINT_RESULT // вывод окон и завершение

		default:
			fmt.Println("Неизвестная команда. Введите ENQUEUE или DISTRIBUTE.")
		}
	}

PRINT_RESULT:
	fmt.Println("\nСостояние окон:")
	for i, w := range windows {
		fmt.Printf("Окно %d (%d мин): %s\n", i+1, w.totalTime, strings.Join(w.clients, " "))
	}
}
