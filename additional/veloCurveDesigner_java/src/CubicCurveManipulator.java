import javafx.application.Application;
import javafx.beans.property.DoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Side;
import javafx.scene.*;
import javafx.scene.chart.NumberAxis;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.stage.Stage;


// TODO: Pastel Color palette
/** Example of how a cubic curve works, drag the anchors around to change the curve. */
public class CubicCurveManipulator extends Application {
    private final int WIDTH = 800;
    private final int HEIGHT = 400;

    private CubicCurve curve = createStartingCurve();


    public static void main(String[] args) throws Exception { launch(args); }
    @Override public void start(final Stage stage) throws Exception {


        Line controlLine1 = new BoundLine(curve.controlX1Property(), curve.controlY1Property(), curve.startXProperty(), curve.startYProperty());
        Line controlLine2 = new BoundLine(curve.controlX2Property(), curve.controlY2Property(), curve.endXProperty(),   curve.endYProperty());

        //Anchor start    = new Anchor(Color.PALEGREEN, curve.startXProperty(),    curve.startYProperty());
        Anchor control1 = new Anchor(Color.RED,      curve.controlX1Property(), curve.controlY1Property());
        Anchor control2 = new Anchor(Color.BLUE, curve.controlX2Property(), curve.controlY2Property());
        //Anchor end      = new Anchor(Color.TOMATO,    curve.endXProperty(),      curve.endYProperty());

        Button btn = new Button();
        btn.setLayoutX(10);
        btn.setLayoutY(10);
        btn.setText("Print Curve Data");
        btn.setOnAction(this::buttonEvent);

        NumberAxis axisX = new NumberAxis(100, 700, 10);
        axisX.setSide(Side.BOTTOM);
        axisX.setLayoutY(this.HEIGHT-20);
        axisX.setPrefWidth(this.WIDTH-200);
        axisX.setLayoutX(100);

        NumberAxis axisY = new NumberAxis(0, 127, 2);
        axisY.setSide(Side.LEFT);
        axisY.setLayoutY(80);
        axisY.setPrefHeight(300);
        axisY.setLayoutX(70);



        stage.setTitle("VeloCurveDesigner 2000");
        //.setScene(new Scene(new Group(controlLine1, controlLine2, curve, start, control1, control2, end), 400, 400, Color.ALICEBLUE));
        stage.setScene(new Scene(new Group(curve, control1, control2, btn, axisX, axisY, controlLine1, controlLine2), this.WIDTH, this.HEIGHT, Color.BLACK));
        stage.setResizable(false);
        stage.show();
    }

    private void buttonEvent(ActionEvent e) {
        this.printCurveData(curve.getStartY(), curve.getControlY1(), curve.getControlY2(), curve.getEndY(), 128);
    }

    /**
    //Map a value from one range (f and t) into another one (maxLim and minLim)
    private double map(double x,double f,double t,double minLim,double maxLim) {
        return (t + (f - t) * ((x - minLim) / (maxLim - minLim)));
    } */


    private void printCurveData(double p1, double p2, double p3, double p4, double stepSize) {
        double step = 1.0 / stepSize;
        for (double t = 0; t < 1; t=t+stepSize ) {
            double x = Math.pow(1-t, 3) * p1    +   3 * Math.pow(1-t, 2)*t*p2   +    3*(1-t)*Math.pow(t,2)*p3   +   Math.pow(t, 3)*p4;
            System.out.println( x + " "+ t );
        }
    }

    private CubicCurve createStartingCurve() {
        CubicCurve curve = new CubicCurve();
        curve.setStartX(100);
        curve.setStartY(this.HEIGHT-20);
        curve.setControlX1(curve.getStartX());
        curve.setControlY1(curve.getStartY());
        curve.setEndX(700);
        curve.setEndY(80);
        curve.setControlX2(curve.getEndX());
        curve.setControlY2(curve.getEndY());

        curve.setStroke(Color.FORESTGREEN);
        curve.setStrokeWidth(4);
        curve.setStrokeLineCap(StrokeLineCap.ROUND);
        curve.setFill(Color.CORNSILK.deriveColor(5, 1.2, 1, 0));
        return curve;
    }

    class BoundLine extends Line {
        BoundLine(DoubleProperty startX, DoubleProperty startY, DoubleProperty endX, DoubleProperty endY) {
            startXProperty().bind(startX);
            startYProperty().bind(startY);
            endXProperty().bind(endX);
            endYProperty().bind(endY);
            setStrokeWidth(2);
            setStroke(Color.GREY.deriveColor(0, 1, 1, 0.5));
            setStrokeLineCap(StrokeLineCap.BUTT);
            getStrokeDashArray().setAll(10.0, 5.0);
        }
    }

    // a draggable anchor displayed around a point.
    // TODO: Drag Boundaries
    class Anchor extends Circle {
        Anchor(Color color, DoubleProperty x, DoubleProperty y) {
            super(x.get(), y.get(), 10);
            setFill(color.deriveColor(1, 1, 1, 0.5));
            setStroke(color);
            setStrokeWidth(2);
            setStrokeType(StrokeType.OUTSIDE);

            x.bind(centerXProperty());
            y.bind(centerYProperty());
            enableDrag();
        }

        // make a node movable by dragging it around with the mouse.
        private void enableDrag() {
            final Delta dragDelta = new Delta();
            setOnMousePressed(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    // record a delta distance for the drag and drop operation.
                    dragDelta.x = getCenterX() - mouseEvent.getX();
                    dragDelta.y = getCenterY() - mouseEvent.getY();
                    getScene().setCursor(Cursor.MOVE);
                }
            });
            setOnMouseReleased(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    getScene().setCursor(Cursor.HAND);
                }
            });
            setOnMouseDragged(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    double newX = mouseEvent.getX() + dragDelta.x;
                    if (newX > 0 && newX < getScene().getWidth()) {
                        setCenterX(newX);
                    }
                    double newY = mouseEvent.getY() + dragDelta.y;
                    if (newY > 0 && newY < getScene().getHeight()) {
                        setCenterY(newY);
                    }
                }
            });
            setOnMouseEntered(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    if (!mouseEvent.isPrimaryButtonDown()) {
                        getScene().setCursor(Cursor.HAND);
                    }
                }
            });
            setOnMouseExited(new EventHandler<MouseEvent>() {
                @Override public void handle(MouseEvent mouseEvent) {
                    if (!mouseEvent.isPrimaryButtonDown()) {
                        getScene().setCursor(Cursor.DEFAULT);
                    }
                }
            });
        }

        // records relative x and y co-ordinates.
        private class Delta { double x, y; }
    }
}