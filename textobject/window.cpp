#include <QtWidgets>
#include <QtSvg>
#include <QPrinter>
#include <QSvgRenderer>
#include <QTextBlockFormat>

#include "window.h"
#include "svgtextobject.h"

#include <QTextDocument>

#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_text.h>
#include <qwt_point_data.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>


Window::Window()
{
    setupGui();
    setupTextObject();

    setWindowTitle("Text Object Example");
}


QRectF cellBounds(QTextDocument& textDocument, QTextTable& table, int row , int col, bool rowCheck)
{
  // Ref: https://stackoverflow.com/questions/27979409/how-to-get-boundingbox-of-a-qtexttablecell
  QTextTableFormat tableFormat = table.format();
  qreal cellBorder = tableFormat.border();
  QTextTableCell cell = table.cellAt(row, col);
  qreal cellPadding = tableFormat.cellPadding();
  QTextBlock next = cell.firstCursorPosition().block();
  QTextBlock last = cell.lastCursorPosition().block();
  QAbstractTextDocumentLayout* layout = textDocument.documentLayout();
  QRectF boundingRect;

  while (next.isValid())
  {
    boundingRect = boundingRect.isNull() ? layout->blockBoundingRect(next) : boundingRect.united(layout->blockBoundingRect(next));
    if (next == last)
    {
      break;
    }
    next = next.next();
  }
  if (!boundingRect.isNull())
  {
    boundingRect.adjust(-cellPadding , -cellPadding, cellPadding, cellPadding);
    /* I am not sure about this part of the code from reference.
    if (rowCheck)
    {
      for (int c = 0; c < table.columns(); c++)
      {
        if (c != col)
        {
          QTextTableCell nextCell = table.cellAt(row,c);
          QRectF nextBounds = cellBounds(textDocument, table, row , c, false);
          if (nextBounds.height() > boundingRect.height())
          {
            boundingRect.setHeight(nextBounds.height());
          }
        }
      }
    }
    */
    // At the moment, the top left point and the width is correct. But the hight is not correct. So we find the height in another way:
    if (row < table.rows()-1)
      // If the row is not last row, we can estimate the height:
    {
      QRectF nextBounds = cellBounds(textDocument, table, row+1 , col, false);
      boundingRect.setHeight(nextBounds.y() - boundingRect.y() - cellPadding - 2 * cellBorder);
    }
  }


  return boundingRect;
  // At the moment, the top left point and the width is correct. But the hight is not correct.

}

//![1]
void Window::insertTextObject()
{
    QString fileName = fileNameLineEdit->text();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error Opening File"),
                             tr("Could not open '%1'").arg(fileName));
    }

    QByteArray svgData = file.readAll();
//![1]

//![2]
    QTextCharFormat svgCharFormat;
    svgCharFormat.setObjectType(SvgTextFormat);
    QSvgRenderer renderer(svgData);

    QImage svgBufferImage(renderer.defaultSize(), QImage::Format_ARGB32);





    QPainter painter(&svgBufferImage);
    renderer.render(&painter, svgBufferImage.rect());

    svgCharFormat.setProperty(SvgData, svgBufferImage);
    QTextCursor cursor = textEdit->textCursor();
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), svgCharFormat);
    textEdit->setTextCursor(cursor);

    /*

    //textDocument.setPageSize(QPageSize(QPageSize::PageSizeId::A4).sizePixels(72));
    QTextCursor textCursor2(textDocument);



    textCursor2.insertText("HelloWelt");
    textCursor2.insertText(QString(QChar::ObjectReplacementCharacter), svgCharFormat);
    textCursor2.insertText("Welt");

    QPrinter printer(QPrinter::PrinterMode::ScreenResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Orientation::Portrait);
    printer.setOutputFormat(QPrinter::OutputFormat::PdfFormat);
    printer.setOutputFileName("C:/Users/Damon/Desktop/textobject/textobject/sample.pdf");
    //textDocument->print(&printer);


    // The resulting pdf of the following is vector graphics:
    QSvgRenderer ren2;
    ren2.load(QString("C:/Users/Damon/Desktop/textobject/textobject/files/heart.svg"));

    QPrinter printer2;
    printer2.setOutputFormat(QPrinter::OutputFormat::PdfFormat);
    printer2.setPaperSize(QPrinter::A4);
    printer2.setOutputFileName("C:/Users/Damon/Desktop/textobject/textobject/sample2.pdf");

    QPainter painter2(&printer2);
    ren2.render(&painter2, QRectF(0,0,100,100));
    painter2.end();

    // End of sample2----------------------------------------

    QPainter painter3;
    ren2.render(&painter3, QRectF(0,0,100,100));
    painter3.end();


    QPrinter printer3;
    painter3.begin(&printer3);
    textDocument->drawContents(&painter3);
    painter3.end();

    printer3.setPaperSize(QPrinter::A4);
    printer3.setPageSize(QPrinter::A4);
    printer3.setOrientation(QPrinter::Orientation::Portrait);
    printer3.setOutputFormat(QPrinter::OutputFormat::PdfFormat);
    printer3.setOutputFileName("C:/Users/Damon/Desktop/textobject/textobject/sample3.pdf");
    textDocument->print(&printer3);

    // Sample 4: works---------------------------------------------------------
    // Ref: https://forum.qt.io/topic/74448/qtextdocument-drawcontents-in-a-qrectf
    QPdfWriter pdfWriter("C:/Users/Damon/Desktop/textobject/textobject/sample4.pdf");
    pdfWriter.setResolution(300);

    QPageSize pageSize(QPageSize::A4);
    QMarginsF margins(10, 10, 10, 10);
    QPageLayout pageLayout(pageSize, QPageLayout::Portrait, margins, QPageLayout::Millimeter);
    pdfWriter.setPageLayout(pageLayout);

    QPainter painter4(&pdfWriter);
    ren2.render(&painter4, QRectF(200,200,400,400));
    //painter4.translate(200,200);

    QTextDocument td4;
    QTextCursor cursor4(&td4);
    cursor4.insertText("hdshsh fdhhdg dhg hghfgh fhgfhg fhghfg hfghfh ghgfhg h");
    td4.drawContents(&painter4); // Draws the contents of the document with painter.
    painter4.end();

    */
    // Sample 5 ----------------------------------------------------------------------
    QwtPlotCurve *const curve=new QwtPlotCurve("Sine");
    QwtPlot *const plot = new QwtPlot(QwtText("CppHelloQwtCreator"));

    plot->setGeometry(0,0,640,400);
    plot->setAxisScale(QwtPlot::xBottom,0.0,2.0*M_PI);
    plot->setAxisScale(QwtPlot::yLeft,-1.0,1.0);
    plot->setAxisTitle(QwtPlot::xBottom,"X axis");
    plot->setAxisTitle(QwtPlot::yLeft,"Y axis");

    std::vector <double> xs;
    std::vector <double> ys;
    for (double x=0;x<2.0*M_PI;x+=(M_PI/10.0))
    {
        xs.push_back(x);
        ys.push_back(std::sin(x));
    }

    QwtPointArrayData * const data =new QwtPointArrayData(&xs[0],&ys[0],xs.size());
    curve->setData(data);
    curve->attach(plot);
    plot->replot();

    QwtPlotGrid grid;
    grid.setPen(Qt::GlobalColor::red, 3, Qt::PenStyle::DashLine);
    grid.enableX(true);
    grid.enableY(true);
    grid.attach(plot);
    plot->replot();

    QString svgPath = "C:/Users/Damon/Desktop/textobject/textobject/sampleQwt.svg";
    int dpiSvg = 72;
    QwtPlotRenderer plotRenderer;
    plotRenderer.renderDocument(plot, svgPath, QSize(400,100));

    // The resulting pdf of the following is vector graphics:
    QSvgRenderer ren5;
    ren5.load(QString("C:/Users/Damon/Desktop/textobject/textobject/sampleQwt.svg"));

    QPdfWriter pdfWriter5("C:/Users/Damon/Desktop/textobject/textobject/sample5.pdf");
    pdfWriter5.setResolution(dpiSvg);

    QPageSize pageSize5(QPageSize::A4);
    QMarginsF margins5(0, 0, 0, 0);
    QPageLayout pageLayout5(pageSize5, QPageLayout::Portrait, margins5, QPageLayout::Point);
    pdfWriter5.setPageLayout(pageLayout5);

    QPainter painter5(&pdfWriter5);

    QTextDocument td5;
    td5.setPageSize(QPageSize(QPageSize::PageSizeId::A4).sizePixels(dpiSvg));
    QTextCursor cursor5(&td5);
    cursor5.insertText("hdshsh fdhhdg dhg hghfgh fhgfhg fhghfg hfghfh ghgfhg h");
    QTextTableFormat tableFormat;
    QVector<QTextLength> vectorTextLengths{
      QTextLength(QTextLength::Type::PercentageLength, 20),
      QTextLength(QTextLength::Type::PercentageLength, 80)
    };
    tableFormat.setColumnWidthConstraints(vectorTextLengths);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle::BorderStyle_Solid);
    tableFormat.setBorderBrush(QBrush{ Qt::SolidPattern });
    tableFormat.setMargin(0);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    QTextTable* table = cursor5.insertTable(4,2, tableFormat);

    QTextBlockFormat blockFormat = table->cellAt(1, 1).firstCursorPosition().blockFormat();

    int height = 100;
    blockFormat.setLineHeight(height, QTextBlockFormat::FixedHeight);
    table->cellAt(1, 1).firstCursorPosition().setBlockFormat(blockFormat);
    table->cellAt(2, 1).firstCursorPosition().setBlockFormat(blockFormat);

    QTextCharFormat charFormat = table->cellAt(1, 1).firstCursorPosition().charFormat();
    charFormat.setBackground(QBrush(Qt::GlobalColor::green));
    table->cellAt(1, 1).setFormat(charFormat);

    td5.drawContents(&painter5); // Draws the contents of the document with painter.

    cursor5.setPosition(table->cellAt(1,1).firstPosition());
    QTextBlock cellTextBlock = table->cellAt(1,1).firstCursorPosition().block();
    QRectF cellRect1 = cellBounds(td5,*table,1,1,true);
    QRectF cellRect2 = cellBounds(td5,*table,2,1,true);
    // At the moment, the top left point and the width is correct. But the hight is not correct.
    // So we reset the height:

    ren5.render(&painter5, cellRect1);
    ren5.render(&painter5, cellRect2);
    //painter4.translate(200,200);

    painter5.end();








}
//![2]

//![3]
void Window::setupTextObject()
{
    QObject *svgInterface = new SvgTextObject;
    svgInterface->setParent(this);
    textEdit->document()->documentLayout()->registerHandler(SvgTextFormat, svgInterface);
    textDocument->documentLayout()->registerHandler(SvgTextFormat, svgInterface);

}
//![3]

void Window::setupGui()
{
    fileNameLabel = new QLabel(tr("Svg File Name:"));
    fileNameLineEdit = new QLineEdit;
    insertTextObjectButton = new QPushButton(tr("Insert Image"));

    fileNameLineEdit->setText(":/files/heart.svg");
    connect(insertTextObjectButton, SIGNAL(clicked()),
            this, SLOT(insertTextObject()));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(fileNameLabel);
    bottomLayout->addWidget(fileNameLineEdit);
    bottomLayout->addWidget(insertTextObjectButton);

    textEdit = new QTextEdit;

    textDocument = new QTextDocument;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}
