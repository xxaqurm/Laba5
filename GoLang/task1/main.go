package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

const (
    ShelvesPerVerticalSection = 5
    VerticalSectionCount      = 1
    TotalItemStorage          = 1500
    StorageZoneCount          = 10
    ShelvesPerZone            = 3
    SlotStorage               = 10
)

type Address struct {
    Zone            int
    Section         int
    VerticalSection int
    Shelf           int
}

type Storage map[Address]map[string]int

func main() {
    storage := make(Storage)
    scanner := bufio.NewScanner(os.Stdin)

    fmt.Println("Для дообавления предмета воспользуйтесь командой ADD (ADD <название> <количество> <ячейка>)")
    fmt.Println("Для удаления предмета воспользуйтесь командой REMOVE (REMOVE <название> <количество> <ячейка>)")
    fmt.Println("Для получения информации о складе воспользуйтесь командой INFO")
    fmt.Println("Для выхода из программы воспользуйтесь командой EXIT")

    for {
        fmt.Print("Введите команду: ")
        if !scanner.Scan() {
            break
        }
        input := scanner.Text()
        fields := strings.Fields(input)
        if len(fields) == 0 {
            continue
        }
        command := strings.ToUpper(fields[0])

        switch command {
        case "ADD", "REMOVE":
            if len(fields) != 4 {
                fmt.Println("Неверное количество аргументов.")
                continue
            }

            itemName := fields[1]
            items, err := strconv.Atoi(fields[2])
            if err != nil || items <= 0 {
                fmt.Println("Некорректное количество предметов.")
                continue
            }
            sectionCode := fields[3]
            if len(sectionCode) != 4 {
                fmt.Println("Код секции должен состоять из 4 символов.")
                continue
            }

            address, valid := parseAddress(sectionCode)
            if !valid || !validateInput(address, items) {
                continue
            }

            if command == "ADD" {
                if getTotalItems(storage[address])+items > SlotStorage {
                    fmt.Printf("Недостаточно места на складе. Максимум в ячейке: %d\n", SlotStorage)
                    continue
                }
                addItem(storage, address, itemName, items)
            } else {
                if _, ok := storage[address]; !ok || storage[address][itemName] < items {
                    fmt.Println("Недостаточно предметов или предмет не найден.")
                    continue
                }
                removeItem(storage, address, itemName, items)
            }

        case "INFO":
            printInfo(storage)

        case "EXIT":
            return

        default:
            fmt.Println("Неизвестная команда.")
        }
        fmt.Println("----------------------------------------")
    }
}

func parseAddress(code string) (Address, bool) {
    zone := int(code[0] - 'A')
    section := int(code[1] - '0')
    verticalSection := int(code[2] - '0')
    shelf := int(code[3] - '0')

    return Address{zone, section, verticalSection, shelf}, true
}

func validateInput(addr Address, items int) bool {
    if addr.Zone < 0 || addr.Zone >= StorageZoneCount {
        fmt.Printf("Некорректная зона. A-%c\n", 'A'+StorageZoneCount-1)
        return false
    }
    if addr.Section < 1 || addr.Section > ShelvesPerZone {
        fmt.Printf("Некорректная секция. 1-%d\n", ShelvesPerZone)
        return false
    }
    if addr.VerticalSection < 1 || addr.VerticalSection > VerticalSectionCount {
        fmt.Printf("Некорректная вертикальная секция. 1-%d\n", VerticalSectionCount)
        return false
    }
    if addr.Shelf < 1 || addr.Shelf > ShelvesPerVerticalSection {
        fmt.Printf("Некорректная полка. 1-%d\n", ShelvesPerVerticalSection)
        return false
    }
    if items <= 0 {
        fmt.Println("Количество должно быть больше 0.")
        return false
    }
    return true
}

func addItem(storage Storage, addr Address, item string, count int) {
    if _, exists := storage[addr]; !exists {
        storage[addr] = make(map[string]int)
    }
    storage[addr][item] += count
    fmt.Printf("Добавлено %d предметов %s в ячейку %c%d%d%d\n", count, item, rune('A'+addr.Zone), addr.Section, addr.VerticalSection, addr.Shelf)
}

func removeItem(storage Storage, addr Address, item string, count int) {
    storage[addr][item] -= count
    fmt.Printf("Удалено %d предметов %s из ячейки %c%d%d%d\n", count, item, rune('A'+addr.Zone), addr.Section, addr.VerticalSection, addr.Shelf)
}

func getTotalItems(cell map[string]int) int {
    total := 0
    for _, v := range cell {
        total += v
    }
    return total
}

func printInfo(storage Storage) {
    fmt.Println("Информация о складе:")
    totalItems := 0
    storageLoad := make([]int, StorageZoneCount)

    for addr, items := range storage {
        for item, count := range items {
            fmt.Printf("Зона: %c, Секция: %d, Вертикальная секция: %d, Полка: %d, Предмет: %s, Количество: %d\n",
                rune('A'+addr.Zone), addr.Section, addr.VerticalSection, addr.Shelf, item, count)
            totalItems += count
            storageLoad[addr.Zone] += count
        }
    }

    fmt.Println("Загрузка склада по зонам:")
    for i := 0; i < StorageZoneCount; i++ {
        fmt.Printf("Зона %c: %d\n", rune('A'+i), storageLoad[i])
    }
    fmt.Printf("Общая загруженность склада: %.1f%%\n", float64(totalItems)/float64(TotalItemStorage)*100)
}
