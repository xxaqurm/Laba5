package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type WindowQueue struct {
	time    int
	clients []string
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	windowCount := 0
	for windowCount < 1 {
		fmt.Print("Введите количество окон: ")
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		n, err := strconv.Atoi(line)
		if err != nil || n < 1 {
			fmt.Println("Количество окон должно быть больше 0.")
			continue
		}
		windowCount = n
	}

	windowQueues := make([]WindowQueue, windowCount)

	numberOfClients := 0
	clients := make([]struct {
		name string
		time int
	}, 0)

	for {
		fmt.Print("Введите команду (ENQUEUE [time], DEQUEUE, EXIT): ")
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)

		// Разбиваем строку на слова
		parts := strings.Fields(line)
		if len(parts) == 0 {
			fmt.Println("Введите команду.")
			continue
		}

		command := strings.ToUpper(parts[0]) // для удобства сравниваем в верхнем регистре

		switch command {
		case "ENQUEUE":
			if len(parts) < 2 {
				fmt.Println("Команда ENQUEUE требует указать время, например: ENQUEUE 5")
				continue
			}
			timeVal, err := strconv.Atoi(parts[1])
			if err != nil || timeVal < 1 {
				fmt.Println("Время должно быть положительным числом.")
				continue
			}
			numberOfClients++
			clientName := "T" + strconv.Itoa(numberOfClients)
			clients = append(clients, struct {
				name string
				time int
			}{name: clientName, time: timeVal})

		case "DEQUEUE":
			if len(clients) == 0 {
				fmt.Println("Нет клиентов в очереди.")
				continue
			}

			for _, client := range clients {
				bestWindow := 0
				bestTime := windowQueues[0].time
				for i := 1; i < len(windowQueues); i++ {
					if windowQueues[i].time < bestTime {
						bestTime = windowQueues[i].time
						bestWindow = i
					}
				}
				windowQueues[bestWindow].time += client.time
				windowQueues[bestWindow].clients = append(windowQueues[bestWindow].clients, client.name)
			}

			goto PrintResult

		case "EXIT":
			return

		default:
			fmt.Println("Неизвестная команда. Введите ENQUEUE, DEQUEUE или EXIT.")
		}
	}

PrintResult:
	for i, window := range windowQueues {
		fmt.Printf("Окно %d (%d мин): ", i+1, window.time)
		for _, client := range window.clients {
			fmt.Print(client, " ")
		}
		fmt.Println()
	}
}
