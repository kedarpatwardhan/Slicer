/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerExtensionsWizardRestartPage_h
#define __qSlicerExtensionsWizardRestartPage_h

// Qt includes
#include <QWizardPage>

// QtGUI includes
#include "qSlicerBaseQTGUIExport.h"

class qSlicerExtensionsWizardRestartPagePrivate;

class Q_SLICER_BASE_QTGUI_EXPORT qSlicerExtensionsWizardRestartPage
  : public QWizardPage
{
  Q_OBJECT
public:
  /// Superclass typedef
  typedef QWizardPage Superclass;

  /// Constructor
  explicit qSlicerExtensionsWizardRestartPage(QWidget* parent = 0);

  /// Destructor
  virtual ~qSlicerExtensionsWizardRestartPage();

  virtual void initializePage();

public slots:
  void restart();

protected:
  QScopedPointer<qSlicerExtensionsWizardRestartPagePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerExtensionsWizardRestartPage);
  Q_DISABLE_COPY(qSlicerExtensionsWizardRestartPage);
};

#endif