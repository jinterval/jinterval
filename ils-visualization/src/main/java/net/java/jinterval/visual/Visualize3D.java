/*
 * Copyright (c) 2012, JInterval Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.visual;

import javafx.animation.RotateTransitionBuilder;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Point3D;
import javafx.scene.DepthTest;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.PolygonBuilder;
import javafx.scene.transform.Shear;
import javafx.scene.transform.Transform;
import javafx.stage.Stage;
import javafx.util.Duration;
import net.java.jinterval.ils.set.AEssR3;
import net.java.jinterval.ils.set.DrawHedrons;

/**
 */
public class Visualize3D extends Application {

    @Override
    public void start(final Stage stage) {
        Group root = new Group();
        Button btn = new Button();
        btn.setText("Say 'Hello World'");
        Scene scene = new Scene(root, 500, 500, Color.BLACK);
        root.setTranslateX(250);
        root.setTranslateY(250);

        Group ilsGroup = new Group();
        root.getChildren().add(btn);
        ilsGroup.getTransforms().add(new Shear());
        ilsGroup.setDepthTest(DepthTest.ENABLE);
        AEssR3.Result ae = Examples3D.initNStar(3.5);
        for (DrawHedrons.Hedron h : ae.hedrons) {
            assert h.xt.getDimension() == h.yt.getDimension();
            Double[] points = new Double[h.xt.getDimension() * 2];
            for (int i = 0; i < h.xt.getDimension(); i++) {
                points[i * 2] = h.xt.getEntry(i).doubleValue();
                points[i * 2 + 1] = h.yt.getEntry(i).doubleValue();
            }
            Polygon poly = PolygonBuilder.create()
                    .points(points)
//                    .transforms(Transform.affine(
//                    h.ex.getEntry(0).doubleValue(), h.ey.getEntry(0).doubleValue(), 0, h.r0.getEntry(0).doubleValue(),
//                    h.ex.getEntry(1).doubleValue(), h.ey.getEntry(1).doubleValue(), 0, h.r0.getEntry(1).doubleValue(),
//                    h.ex.getEntry(2).doubleValue(), h.ey.getEntry(2).doubleValue(), 0, h.r0.getEntry(2).doubleValue()))
                    .build();
            Color c = new Color(h.c.getRed() / 255., h.c.getGreen() / 255., h.c.getBlue() / 255., 1);//, h.transp);
            poly.setFill(c);
            poly.setStroke(Color.YELLOW);
            poly.setStrokeWidth(3e-3);
            ilsGroup.getChildren().add(poly);
        }
        root.getChildren().add(ilsGroup);

        ilsGroup.setScaleX(100*100);
        ilsGroup.setScaleY(100*100);
        ilsGroup.setScaleZ(100*100);
        ilsGroup.setRotationAxis(new Point3D(1, 1, 1));

        RotateTransitionBuilder.create()
                .node(ilsGroup)
                .duration(Duration.millis(5000))
                .fromAngle(0)
                .byAngle(360)
                .cycleCount(Timeline.INDEFINITE)
                .autoReverse(true)
                .build()
                .play();

        stage.setTitle("NStar visualization");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}