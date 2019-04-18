/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TRACKSLIDER_H
#define TRACKSLIDER_H

#include "config.h"

#include <stdbool.h>

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSize>
#include <QLabel>

class QEvent;

class Application;
#ifdef HAVE_MOODBAR
class MoodbarProxyStyle;
#endif
class Ui_TrackSlider;

class TrackSlider : public QWidget {
  Q_OBJECT

 public:
  TrackSlider(QWidget* parent = nullptr);
  ~TrackSlider();

  void SetApplication(Application* app);

  // QWidget
  QSize sizeHint() const;

  // QObject
  bool event(QEvent *);

#ifdef HAVE_MOODBAR
  MoodbarProxyStyle *moodbar_style() const { return moodbar_style_; }
#endif


  static const char* kSettingsGroup;

 public slots:
  void SetValue(int elapsed, int total);
  void SetStopped();
  void SetCanSeek(bool can_seek);
  void Seek(int gap);

 signals:
  void ValueChanged(int value);
  void ValueChangedSeconds(int value);

 private slots:
  void ValueMaybeChanged(int value);
  void ToggleTimeDisplay();

 private:
  void UpdateTimes(int elapsed);
  void UpdateLabelWidth();
  void UpdateLabelWidth(QLabel* label, const QString& text);

 private:
  Ui_TrackSlider* ui_;

#ifdef HAVE_MOODBAR
  MoodbarProxyStyle* moodbar_style_;
#endif

  bool setting_value_;
  bool show_remaining_time_;
  int slider_maximum_value_; //we cache it to avoid unnecessary updates
};

#endif  // TRACKSLIDER_H
