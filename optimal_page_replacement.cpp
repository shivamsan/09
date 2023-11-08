#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, frames;
    cout << "Enter the number of frames: ";
    cin >> frames;

    cout << "Enter the number of page references: ";
    cin >> n;

    vector<int> pageReferences(n);
    cout << "Enter the page references: ";
    for (int i = 0; i < n; i++) {
        cin >> pageReferences[i];
    }

    vector<int> frameTable(frames, -1);
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pageReferences[i];
        bool pageFound = false;

        for (int j = 0; j < frames; j++) {
            if (frameTable[j] == page) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            int replaceIndex = -1;
            int farthestUse = -1;

            for (int j = 0; j < frames; j++) {
                int nextPageIndex = i + 1;
                while (nextPageIndex < n) {
                    if (pageReferences[nextPageIndex] == frameTable[j]) {
                        if (nextPageIndex > farthestUse) {
                            farthestUse = nextPageIndex;
                            replaceIndex = j;
                        }
                        break;
                    }
                    nextPageIndex++;
                }
                if (nextPageIndex == n) {
                    replaceIndex = j;
                    break;
                }
            }

            frameTable[replaceIndex] = page;
            pageFaults++;
        }

        cout << "Page " << page << ": ";
        for (int j = 0; j < frames; j++) {
            if (frameTable[j] == -1) {
                cout << " - ";
            } else {
                cout << " " << frameTable[j];
            }
        }
        cout << endl;
    }

    cout << "Total page faults: " << pageFaults << endl;

    return 0;
}
