#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <sstream>    // For std::stringstream
#include <string>
#include <stdexcept>  // For runtime_error and custom exception
#include <sstream>    // For std::istringstream

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the central widget and set layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create text areas
    textArea1 = new QTextEdit(this);
    textArea2 = new QTextEdit(this);

    // Optionally set placeholder text
    textArea1->setPlaceholderText("Enter your code here...");
    textArea2->setPlaceholderText("Lexer output will appear here...");
    textArea2->setReadOnly(true); // Make the output area read-only

    // Create button
    button = new QPushButton("Submit", this);

    // Add widgets to the layout
    layout->addWidget(textArea1);
    layout->addWidget(button);
    layout->addWidget(textArea2);

    // Set the central widget to be our layout container
    setCentralWidget(centralWidget);

    // Set the window title
    setWindowTitle("Python Compiler");

    // Connect the button click signal to the slot
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClick);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onButtonClick()
{
    // Get the text from textArea1
    QString inputText = textArea1->toPlainText();

    // Convert QString to std::string
    std::string inputStdString = inputText.toStdString();

    // Use a std::istringstream to read from the string
    std::istringstream source(inputStdString);

    pyc::Lexer lexer(source);

    // Process tokens
    std::stringstream outputStream;

    try {
        while (lexer.is_token_available()) {
            const pyc::Token &token = lexer.next_token();

            switch (token.get_type()) {
            case pyc::TokenType::IDENTIFIER:
            case pyc::TokenType::KEYWORD:
            case pyc::TokenType::STRING: {  // Case for strings
                const pyc::Word &word = static_cast<const pyc::Word&>(token);
                outputStream << word << std::endl;
                break;
            }
            case pyc::TokenType::NUMBER: {
                if (token.get_tag() == pyc::TagType::INTEGER) {
                    const pyc::Integer &integer = static_cast<const pyc::Integer &>(token);
                    outputStream << integer << std::endl;
                } else {
                    const pyc::Real &real = static_cast<const pyc::Real &>(token);
                    outputStream << real << std::endl;
                }
                break;
            }
            default:
                outputStream << token << std::endl;
                break;
            }
        }
    } catch (const std::exception& e) {
        outputStream << "Error while processing tokens: " << e.what() << std::endl;
    }

    // Display the output in textArea2
    QString outputText = QString::fromStdString(outputStream.str());
    textArea2->setPlainText(outputText);
}
