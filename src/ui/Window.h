#ifndef OTTER_WINDOW_H
#define OTTER_WINDOW_H

#include <QtCore/QUrl>
#include <QtGui/QIcon>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets/QWidget>
#include <QtWidgets/QUndoStack>
#include <QtWebKitWidgets/QWebPage>

namespace Otter
{

namespace Ui
{
	class Window;
}

enum WebAction
{
	NoAction = 0,
	OpenLinkAction,
	OpenLinkInNewWindowAction,
	OpenLinkInThisWindowAction,
	OpenFrameInNewWindowAction,
	DownloadLinkToDiskAction,
	CopyLinkToClipboardAction,
	OpenImageInNewWindowAction,
	DownloadImageToDiskAction,
	CopyImageToClipboardAction,
	CopyImageUrlToClipboardAction,
	GoBackAction,
	GoForwardAction,
	RewindBackAction,
	RewindForwardAction,
	StopAction,
	StopScheduledPageRefreshAction,
	ReloadAction,
	ReloadAndBypassCacheAction,
	ReloadTimeAction,
	CutAction,
	CopyAction,
	PasteAction,
	DeleteAction,
	SelectAllAction,
	UndoAction,
	RedoAction,
	InspectElementAction,
	PrintAction,
	BookmarkAction,
	CopyAddressAction,
	ShowSourceAction,
	ValidateAction,
	ContentBlockingAction,
	WebsitePreferencesAction,
	FullScreenAction
};

class Window : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)
	Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)
	Q_PROPERTY(QIcon icon READ getIcon NOTIFY iconChanged)
	Q_PROPERTY(int zoom READ getZoom WRITE setZoom NOTIFY zoomChanged)
	Q_PROPERTY(bool isClonable READ isClonable)
	Q_PROPERTY(bool isEmpty READ isEmpty)
	Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)
	Q_PROPERTY(bool isPinned READ isPinned WRITE setPinned NOTIFY isPinnedChanged)
	Q_PROPERTY(bool isPrivate READ isPrivate WRITE setPrivate NOTIFY isPrivateChanged)

public:
	explicit Window(QWidget *parent = NULL);
	~Window();

	virtual void print(QPrinter *printer);
	virtual Window* clone(QWidget *parent = NULL);
	virtual QAction* getAction(WebAction action);
	virtual QUndoStack* getUndoStack();
	virtual QString getTitle() const;
	virtual QUrl getUrl() const;
	virtual QIcon getIcon() const;
	virtual int getZoom() const;
	virtual bool isClonable() const;
	virtual bool isEmpty() const;
	virtual bool isLoading() const;
	virtual bool isPinned() const;
	virtual bool isPrivate() const;

public slots:
	virtual void triggerAction(WebAction action, bool checked = false);
	virtual void reload();
	virtual void stop();
	virtual void goBack();
	virtual void goForward();
	virtual void undo();
	virtual void redo();
	virtual void cut();
	virtual void copy();
	virtual void paste();
	virtual void remove();
	virtual void selectAll();
	virtual void zoomIn();
	virtual void zoomOut();
	virtual void zoomOriginal();
	virtual void setZoom(int zoom);
	virtual void setUrl(const QUrl &url);
	virtual void setPinned(bool pinned);
	virtual void setPrivate(bool enabled);

protected:
	void changeEvent(QEvent *event);
	QWebPage::WebAction mapAction(WebAction action) const;

protected slots:
	void triggerAction();
	void loadUrl();
	void loadStarted();
	void loadFinished(bool ok);
	void notifyTitleChanged();
	void notifyUrlChanged(const QUrl &url);
	void notifyIconChanged();
	void showMenu(const QPoint &position);

private:
	QHash<WebAction, QAction*> m_customActions;
	bool m_isLoading;
	bool m_isPinned;
	Ui::Window *m_ui;

signals:
	void titleChanged(const QString &title);
	void urlChanged(const QUrl &url);
	void iconChanged(const QIcon &icon);
	void loadingChanged(bool loading);
	void undoTextChanged(const QString &undoText);
	void redoTextChanged(const QString &redoText);
	void zoomChanged(int zoom);
	void isPinnedChanged(bool pinned);
	void isPrivateChanged(bool pinned);
	void canUndoChanged(bool canUndo);
	void canRedoChanged(bool canRedo);
};

}

#endif
