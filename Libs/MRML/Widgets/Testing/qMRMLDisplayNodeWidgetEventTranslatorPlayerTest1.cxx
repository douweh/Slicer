/*=========================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Benjamin LONG, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

=========================================================================*/

// Qt includes
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QStandardItemModel>
#include <QTimer>
#include <QTreeView>

// CTK includes
#include "ctkCallback.h"
#include "ctkEventTranslatorPlayerWidget.h"
#include "ctkQtTestingUtility.h"

// qMRML includes
#include "qMRMLDisplayNodeWidget.h"

// MRML includes
#include <vtkMRMLModelDisplayNode.h>

// VTK includes
#include <vtkSmartPointer.h>

// STD includes
#include <cstdlib>
#include <iostream>

namespace
{
//-----------------------------------------------------------------------------
void checkFinalWidgetState(void* data)
  {
  qMRMLDisplayNodeWidget* widget = reinterpret_cast<qMRMLDisplayNodeWidget*>(data);

  CTKCOMPARE(widget->opacity(), 0.55);
//  CTKCOMPARE(widget->ambient(), 0.1);
  CTKCOMPARE(widget->diffuse(), 0.8);
  CTKCOMPARE(widget->specular(), 0.5);
  CTKCOMPARE(widget->visibility(), false);
  CTKCOMPARE(widget->selected(), true);
  CTKCOMPARE(widget->clipping(), true);
  CTKCOMPARE(widget->sliceIntersectionVisible(), true);
  CTKCOMPARE(widget->backfaceCulling(), false);
  }
}

//-----------------------------------------------------------------------------
int qMRMLDisplayNodeWidgetEventTranslatorPlayerTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  QString xmlDirectory = QString(argv[1]) + "/Libs/MRML/Widgets/Testing/";

  // ------------------------
  ctkEventTranslatorPlayerWidget etpWidget;
  ctkQtTestingUtility* testUtility = new ctkQtTestingUtility(&etpWidget);
  etpWidget.setTestUtility(testUtility);

  // Test case 1
  qMRMLDisplayNodeWidget* widget = new qMRMLDisplayNodeWidget();

  vtkSmartPointer< vtkMRMLModelDisplayNode > displayNode =
    vtkSmartPointer< vtkMRMLModelDisplayNode >::New();

  widget->setMRMLDisplayNode(displayNode);

  etpWidget.addTestCase(widget,
                        xmlDirectory + "qMRMLDisplayNodeWidgetEventTranslatorPlayerTest1.xml",
                        &checkFinalWidgetState);

  // ------------------------
  if (!app.arguments().contains("-I"))
    {
    QTimer::singleShot(0, &etpWidget, SLOT(play()));
    }

  etpWidget.show();
  return app.exec();
}
